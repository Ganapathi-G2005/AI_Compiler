import pandas as pd
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
import joblib # <-- IMPORT JOBLIB

def train_model(csv_file_path):
    """
    Loads data from a CSV, trains a Random Forest model, and prints the evaluation.
    Performs hyperparameter tuning using GridSearchCV.
    
    *** ADDED: Saves the best-performing model to a file. ***
    """
    
    # --- 1. DATA LOADING ---
    # Load the dataset from the CSV file using pandas
    try:
        data = pd.read_csv(csv_file_path)
    except FileNotFoundError:
        print(f"Error: The file '{csv_file_path}' was not found.")
        print("Please make sure 'features.csv' is in the same directory as this script.")
        return
    except Exception as e:
        print(f"An error occurred while reading the file: {e}")
        return

    print(f"Successfully loaded data from '{csv_file_path}'.")
    print(f"Total rows: {len(data)}")
    print("---")

    # --- 2. DATA PREPARATION ---
    # Separate the features (X) from the target label (y)
    
    # X gets all rows (:) and all columns *except* the last one (:-1)
    X = data.iloc[:, :-1]
    
    # y gets all rows (:) and *only* the last column (-1)
    y = data.iloc[:, -1]

    print(f"Features (X) shape: {X.shape}")
    print(f"Labels (y) shape: {y.shape}")
    print("---")

    # --- 3. DATA SPLITTING ---
    # Split the data into a training set and a testing set.
    # The model learns from the training set.
    # We test its performance on the unseen testing set.
    
    # test_size=0.2 means 20% of the data will be for testing, 80% for training.
    # random_state=42 ensures we get the same "random" split every time we run
    # this script, making our results reproducible.
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    print(f"Training samples: {len(X_train)}")
    print(f"Testing samples: {len(X_test)}")
    print("---")

    # --- 4. MODEL INITIALIZATION ---
    # Initialize the *base* Random Forest Classifier.
    # The hyperparameter tuning will search for the best settings *for* this model.
    # random_state=42 ensures the model building is reproducible.
    model = RandomForestClassifier(random_state=42)

    # --- 5. HYPERPARAMETER TUNING ---
    print("Starting hyperparameter tuning with GridSearchCV...")

    # Define the "grid" of parameters to search.
    # We'll test different numbers of trees (n_estimators)
    # and different tree depths (max_depth).
    param_grid = {
        'n_estimators': [50, 100, 200],
        'max_depth': [None, 10, 20, 30],
        'min_samples_split': [2, 5, 10],
        'min_samples_leaf': [1, 2, 4]
    }
    
    # NOTE: Your dataset is very small (47 training samples).
    # This means cross-validation (cv) is splitting tiny data.
    # We'll use cv=3 (3 folds) as 5 might be too many.
    # n_jobs=-1 uses all available CPU cores to speed up the search.
    # We are tuning for 'accuracy'.
    cv_folds = min(3, len(X_train) // len(y.unique())) # Heuristic to avoid errors if a class has < 3 samples
    if cv_folds < 2:
        print("Not enough samples for cross-validation, defaulting to cv=2")
        cv_folds = 2

    grid_search = GridSearchCV(estimator=model, 
                               param_grid=param_grid, 
                               cv=cv_folds, 
                               n_jobs=-1, 
                               scoring='accuracy',
                               verbose=1) # verbose=1 shows progress

    # "Fit" the grid search to the training data. This will find the best
    # combination of parameters from the param_grid.
    grid_search.fit(X_train, y_train)

    # Get the best model found by the grid search
    best_model = grid_search.best_estimator_

    print("Model tuning complete.")
    print(f"Best parameters found: {grid_search.best_params_}")
    print("---")


    # --- 6. PREDICTION ---
    # Use the *best_model* (the tuned model) to make predictions
    y_pred = best_model.predict(X_test)

    # --- 7. EVALUATION ---
    # Compare the model's predictions (y_pred) with the true labels (y_test)
    # to see how well it performed.
    
    # Accuracy is the percentage of correct predictions.
    accuracy = accuracy_score(y_test, y_pred)
    
    # The classification report gives a detailed breakdown of performance
    # for each individual class (1, 2, 3, 4, 5).
    # We use the sorted unique values from the original 'y' to create target names
    report = classification_report(y_test, y_pred, target_names=[f"Class {i}" for i in sorted(y.unique())], zero_division=0)

    print("--- TUNED MODEL EVALUATION RESULTS ---")
    print(f"Accuracy on Test Set: {accuracy * 100:.2f}%")
    print("\nClassification Report:")
    print(report)
    print("----------------------------------")
    
    # --- CAVEAT ---
    # Your dataset is very small (only 59 rows).
    # This means the test set is also tiny (around 12 rows).
    # The accuracy score can change *a lot* based on just one or two wrong
    # predictions. For a real-world project, you would need much more
    # data to build a reliable and robust model.
    print("\nNOTE: This is a good start, but the dataset is very small.")
    print("Hyperparameter tuning on small data can be unstable, but this is the correct process.")


    # --- 8. SAVE THE TRAINED MODEL ---
    # This is the new, crucial step.
    # We save the 'best_model' found by GridSearchCV to a file.
    model_filename = 'compiler_model.joblib'
    joblib.dump(best_model, model_filename)
    print("----------------------------------")
    print(f"Tuned model saved successfully to '{model_filename}'")
    print("----------------------------------")


if __name__ == "__main__":
    # This block runs when the script is executed directly
    train_model(csv_file_path="features.csv")

