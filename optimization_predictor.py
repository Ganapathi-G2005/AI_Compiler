#!/usr/bin/env python3
"""
Optimization Predictor System

This system takes C code as input, generates IR, extracts features, 
and predicts the best optimization technique using a trained ML model.
"""

import os
import sys
import joblib
import numpy as np
import warnings
from pathlib import Path

# Import our existing feature extraction system
from ir_feature_extractor import IRFeatureExtractor, generate_ir_from_c_file

# Import optimizer
from optimizer import optimize_ir

# Suppress sklearn warnings about feature names
warnings.filterwarnings("ignore", message="X does not have valid feature names")

class OptimizationPredictor:
    """
    A complete system for predicting the best optimization technique for C code.
    """
    
    def __init__(self, model_path='compiler_model.joblib'):
        """
        Initialize the predictor with a trained model.
        
        Args:
            model_path (str): Path to the saved model file
        """
        self.model_path = model_path
        self.model = None
        self.optimization_labels = {
            1: "Constant Folding",
            2: "Dead Code Elimination", 
            3: "Common Subexpression Elimination",
            4: "Strength Reduction",
            5: "Loop-Invariant Code Motion"
        }
        
        # Feature names for reference
        self.feature_names = [
            'Instruction_Count', 'Basic_Block_Count', 'Cyclomatic_Complexity',
            'Variable_To_Instruction_Ratio', 'Constant_Assignment_Count', 
            'Constant_Operand_Ratio', 'Defined_But_Unused_Var_Count',
            'Unreachable_Block_Count', 'Redundant_Expression_Count',
            'Expression_Complexity_Score', 'Induction_Variable_Count',
            'Expensive_Op_In_Loop_Count', 'Loop_Depth', 'Invariant_Expression_Count'
        ]
        
        self.load_model()
    
    def load_model(self):
        """Load the trained model from file."""
        try:
            if not os.path.exists(self.model_path):
                raise FileNotFoundError(f"Model file '{self.model_path}' not found!")
            
            self.model = joblib.load(self.model_path)
            
        except Exception as e:
            print(f"Error loading model: {e}")
            sys.exit(1)
    
    def extract_features_from_c_code(self, c_code_input):
        """
        Extract features from C code (either file path or code string).
        
        Args:
            c_code_input (str): Either a file path to C code or C code as string
            
        Returns:
            tuple: (features_array, ir_code, feature_dict) or (None, None, None) if failed
        """
        
        # Determine if input is a file path or code string
        if os.path.exists(c_code_input):
            # It's a file path
            c_file_path = c_code_input
        else:
            # It's code as string, save to temporary file
            temp_file = "temp_input.c"
            try:
                with open(temp_file, 'w') as f:
                    f.write(c_code_input)
                c_file_path = temp_file
            except Exception as e:
                return None, None, None
        
        try:
            # Generate IR from C code
            ir_code = generate_ir_from_c_file(c_file_path)
            
            if ir_code is None or ir_code.strip() == "":
                return None, None, None
            
            # Extract features from IR
            extractor = IRFeatureExtractor(ir_code)
            features = extractor.extract_features()
            
            # Convert to numpy array in the correct order
            feature_values = [features[name] for name in self.feature_names]
            features_array = np.array(feature_values).reshape(1, -1)
            
            # Clean up temporary file if created
            if c_code_input != c_file_path and os.path.exists(temp_file):
                os.remove(temp_file)
            
            return features_array, ir_code, features
            
        except Exception as e:
            # Clean up temporary file if created
            if c_code_input != c_file_path and os.path.exists("temp_input.c"):
                os.remove("temp_input.c")
            return None, None, None
    
    def predict_optimization(self, c_code_input, show_details=True):
        """
        Predict the best optimization technique for given C code.
        
        Args:
            c_code_input (str): Either file path to C code or C code as string
            show_details (bool): Whether to show detailed analysis
            
        Returns:
            dict: Prediction results with confidence scores
        """
        
        # Extract features
        features_array, ir_code, feature_dict = self.extract_features_from_c_code(c_code_input)
        
        if features_array is None:
            return {"error": "Failed to extract features from C code"}
        
        try:
            # Make prediction
            prediction = self.model.predict(features_array)[0]
            prediction_proba = self.model.predict_proba(features_array)[0]
            
            # Get confidence scores for all optimizations
            confidence_scores = {}
            for i, prob in enumerate(prediction_proba):
                opt_label = self.optimization_labels[i + 1]
                confidence_scores[opt_label] = prob * 100
            
            # Sort by confidence
            sorted_predictions = sorted(confidence_scores.items(), key=lambda x: x[1], reverse=True)
            
            # Prepare results
            results = {
                "predicted_optimization": self.optimization_labels[prediction],
                "confidence": confidence_scores[self.optimization_labels[prediction]],
                "all_predictions": sorted_predictions,
                "features": feature_dict,
                "ir_code": ir_code
            }
            
            # Display results
            self.display_results(results, show_details)
            
            # Automatically apply the predicted optimization
            self._apply_optimization(results["predicted_optimization"])
            
            return results
            
        except Exception as e:
            return {"error": f"Prediction failed: {e}"}
    
    def display_results(self, results, show_details=True):
        """Display prediction results in a formatted way."""
        
        if "error" in results:
            print(f"Error: {results['error']}")
            return
        
        # Just print the optimization name
        predicted_opt = results["predicted_optimization"]
        print(predicted_opt)
    
    def _apply_optimization(self, optimization_name):
        """
        Apply the predicted optimization to the original IR.
        
        Args:
            optimization_name: Name of the optimization to apply
        """
        try:
            # Check if original_ic.txt exists
            if not os.path.exists('original_ic.txt'):
                print("Warning: original_ic.txt not found. Optimization skipped.")
                return
            
            # Apply optimization
            success = optimize_ir('original_ic.txt', [optimization_name], 'optimized_ic.txt')
            
            if success:
                # Print Done message as requested
                print("Done")
            else:
                print("Warning: Optimization failed.")
                
        except Exception as e:
            print(f"Warning: Could not apply optimization: {e}")
    
    def explain_prediction(self, optimization, features):
        """Provide explanation for why this optimization was recommended."""
        
        explanations = {
            "Constant Folding": [
                f"High constant usage ({features['Constant_Assignment_Count']} assignments, {features['Constant_Operand_Ratio']:.1%} operands)",
                "Many compile-time computable expressions detected"
            ],
            "Common Subexpression Elimination": [
                f"Found {features['Redundant_Expression_Count']} redundant expressions",
                f"Expression complexity score: {features['Expression_Complexity_Score']}"
            ],
            "Dead Code Elimination": [
                f"Detected {features['Defined_But_Unused_Var_Count']} unused variables",
                f"Found {features['Unreachable_Block_Count']} unreachable code blocks"
            ],
            "Loop-Invariant Code Motion": [
                f"Loop depth: {features['Loop_Depth']}",
                f"Found {features['Invariant_Expression_Count']} loop-invariant expressions"
            ],
            "Strength Reduction": [
                f"Found {features['Induction_Variable_Count']} induction variables",
                f"Detected {features['Expensive_Op_In_Loop_Count']} expensive operations in loops"
            ]
        }
        
        if optimization in explanations:
            for reason in explanations[optimization]:
                print(f"  • {reason}")
        else:
            print("  • Analysis based on overall code characteristics")

def main():
    """Main function for command-line usage."""
    
    # Initialize predictor
    predictor = OptimizationPredictor()
    
    if len(sys.argv) < 2:
        print("Usage: python optimization_predictor.py <c_file_path>")
        return
    
    # File mode
    c_file_path = sys.argv[1]
    
    if not os.path.exists(c_file_path):
        print(f"Error: File '{c_file_path}' not found!")
        return
    
    predictor.predict_optimization(c_file_path)

if __name__ == "__main__":
    main()