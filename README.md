# 🍽️ Restaurant Bot - AI-Powered Menu Recommendation System

A sophisticated C++ restaurant ordering system that uses machine learning to provide personalized menu recommendations based on user taste preferences. The bot learns from user feedback through gradient descent optimization to continuously improve suggestions.

## 🌟 Features

### Core Functionality
- **AI-Powered Recommendations**: Intelligent menu suggestions based on taste preferences (sweet, sour, bitter, salty, savory)
- **Machine Learning**: Gradient descent algorithm that learns from user feedback
- **Dual Learning System**: 
  - Global feedback (yes/no responses)
  - Taste-specific preference matching
- **Manual Mode**: Traditional menu browsing and selection
- **Item Customization**: Customize each item with specific options (heat level, toppings, etc.)
- **Weight Persistence**: Learning weights saved to JSON for continuous improvement

### Menu Categories
- 🥖 **Starters** - Appetizing first courses
- 🥗 **Salads** - Fresh and healthy options
- 🍝 **Main Courses** - Hearty entrees
- 🥤 **Drinks** - Refreshing beverages
- 🧀 **Appetizers** - Small bites
- 🍰 **Desserts** - Sweet finishes

## 🏗️ Architecture

### Modular Design
```
restaurant_bot/
├── main.cpp                 # Entry point and main flow
├── ai_mode.cpp             # AI suggestion logic
├── manual_mode.cpp         # Manual menu selection
├── common.cpp              # Shared utilities
├── girdi.cpp               # JSON menu loading
├── restaurant_bot.h        # Core data structures
├── modes.h                 # Function declarations
├── shared_data.h           # Global data declarations
├── menu.json               # Restaurant menu data
├── weights.json            # ML learning weights
├── CMakeLists.txt          # CMake build configuration
├── cmake_build.sh          # Build script
└── compile.sh              # Alternative g++ compilation
```

## 🔧 Technical Stack

- **Language**: C++17
- **JSON Library**: [nlohmann/json](https://github.com/nlohmann/json)
- **Build System**: CMake 3.10+
- **Learning Algorithm**: Gradient Descent with dual learning rates
  - α = 0.1 (global feedback)
  - β = 0.05 (taste-specific feedback)

## 📦 Installation

### Prerequisites
- C++17 compatible compiler (g++ 7.0+, clang 5.0+, MSVC 2017+)
- CMake 3.10 or higher
- Git (optional, for cloning)

### Building with CMake (Recommended)

```bash
# Clone or navigate to the project directory
cd restaurent_bot

# Make build script executable
chmod +x cmake_build.sh

# Build the project
./cmake_build.sh
```

The build script will:
1. Create a `build/` directory
2. Download nlohmann/json if not installed
3. Compile all source files
4. Copy JSON data files to build directory

### Alternative: Direct g++ Compilation

```bash
chmod +x compile.sh
./compile.sh
```

## 🚀 Usage

### Running the Program

```bash
# If built with CMake
./build/restaurant_bot

# If built with compile.sh
./restaurant_bot
```

### AI Mode Workflow

1. **User Introduction**: Enter your name
2. **Taste Preference Setup**: 
   - Choose "balanced" for default (all values = 5)
   - Or enter custom values (0-10 scale) for each taste dimension
3. **AI Suggestions**: For each category:
   - AI suggests best matching item
   - View taste profile and match score
   - Accept (yes), reject (no), or skip category
4. **Customization**: Customize accepted items (heat level, toppings, etc.)
5. **Weight Learning**: System updates learning weights based on your feedback
6. **Manual Adjustment**: Option to modify menu after AI completion

### Manual Mode Workflow

1. **Browse Menu**: View all available items
2. **Add Items**: Search and add items by name
3. **Customize**: Set preferences for each item
4. **Update/Delete**: Modify or remove items from your order
5. **Finalize**: Complete your order

## 🧠 Machine Learning Details

### Distance Calculation
The system calculates how well an item matches your preferences using:

```cpp
distance = sqrt(extraWeight × Σ(weight_i × taste_value_i)²)
```

Higher scores indicate better matches.

### Weight Update Formula
After each feedback, weights are updated using:

```cpp
w_i = w_i + α × global_error × (item_i / 10) + β × (user_pref_i - item_i) / 10
```

Where:
- `α` = learning rate for yes/no feedback
- `β` = learning rate for taste-specific feedback
- `global_error` = 1 for "yes", -1 for "no"

### Persistent Learning
All learned weights are saved to `weights.json` and persist across sessions, allowing the system to improve over time.

## 📊 Data Format

### menu.json Structure
```json
{
  "starters": [
    {
      "name": "Bruschetta",
      "price": 8,
      "taste_balance": {
        "sweet": 3,
        "sour": 7,
        "bitter": 2,
        "salty": 4,
        "savory": 6
      }
    }
  ]
}
```

### weights.json Structure
```json
{
  "starters": {
    "extra_weight": 0.816,
    "taste_balance": {
      "sweet": 0.143,
      "sour": 0.038,
      "bitter": 0.073,
      "salty": 0.037,
      "savory": 0.043
    }
  }
}
```

## 🎯 Customization Options

Each menu category has unique customization features:

- **Starters**: Heat level (mild/medium/hot)
- **Salads**: Extra toppings ($2.25)
- **Main Courses**: Vegetarian option
- **Drinks**: Alcoholic ($2.50) / Carbonated ($0.50)
- **Appetizers**: Before/after main course
- **Desserts**: Chocolate addition ($1.50)

## 🛠️ Development

### Adding New Menu Items

1. Edit `menu.json`
2. Add item with required fields (name, price, taste_balance)
3. Rebuild and run

### Modifying Learning Algorithm

Edit the `updateWeightsFromFeedback()` function in `restaurant_bot.h` to adjust:
- Learning rates (α, β)
- Update formula
- Weight constraints

### Build Options

```bash
# Debug build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# Clean build
rm -rf build
./cmake_build.sh
```

## 📝 Example Session

```
Welcome to the STC Restaurant
=== User Information ===
Enter your first name: John
Enter your last name: Doe

=== Mode Selection ===
Would you like AI-powered suggestions? (yes/no): yes

=== Taste Preference Setup ===
Do you want a 'balanced' menu or 'custom' taste preferences? balanced
Balanced taste profile selected (all values set to 5)

--- STARTER SUGGESTION ---
Item: Caprese Salad ($9)
Taste: Sweet=4, Sour=5, Bitter=1, Salty=5, Savory=7
Match Score: 15.2
Is this okay? (yes/no/skip): yes

[Customization and learning process continues...]

========================================
         FINAL ORDER SUMMARY
========================================
Customer: John Doe
Total Items: 6
Total Cost: $67
========================================
```

## 🤝 Contributing

Contributions are welcome! Areas for improvement:
- Additional learning algorithms
- More menu categories
- GUI interface
- Database integration
- Multi-user support
- Order history tracking

## 📄 License

This project is open source and available for educational purposes.

## 👥 Authors

- **Tunay** - Initial work and development

## 🙏 Acknowledgments

- [nlohmann/json](https://github.com/nlohmann/json) for excellent JSON library
- Gradient descent implementation inspired by machine learning principles
- Modular architecture design patterns

## 📞 Support

For issues, questions, or suggestions:
- Open an issue in the repository
- Contact the development team

---

**Enjoy your personalized dining experience! 🍽️✨**
