# Live Election Vote Counter

A high-performance, real-time vote tracking system built in C++ that provides O(log n) vote updates and instant aggregated results using Fenwick Trees (Binary Indexed Trees).

## 🎯 Overview

The Live Election Vote Counter is designed to handle continuous vote updates in real-time while maintaining fast query performance. It's perfect for:

- National and regional election result tracking
- Internal political party vote tally systems
- Real-time polling data aggregation
- Non-political live counting (sports scoring, contest rankings)

## 🚀 Key Features

- **O(log n) Efficiency**: Fast vote updates and queries even with millions of votes
- **Instant Aggregated Results**: Get totals for candidates, districts, or entire regions instantly
- **Multiple Granularity Levels**: Support queries from small precincts to national totals
- **Real-time Updates**: Process vote updates as they come in from precincts
- **Audit Trail**: Complete vote history for transparency and verification
- **Scalable Architecture**: Handle elections of any size efficiently

## 🏗️ Architecture

### Core Components

1. **FenwickTree**: Implements the Binary Indexed Tree data structure for O(log n) operations
2. **VoteManager**: Handles vote operations and candidate management
3. **ElectionSystem**: High-level interface for election management

### Data Structure

The system uses Fenwick Trees (Binary Indexed Trees) which provide:
- **Point Updates**: O(log n) time to add/subtract votes
- **Range Queries**: O(log n) time to get vote totals
- **Prefix Sums**: Fast aggregation of vote counts

## 📋 Requirements

- C++17 or later
- CMake 3.10 or later
- A modern C++ compiler (GCC 7+, Clang 5+, MSVC 2017+)

## 🛠️ Building the Project

### Prerequisites

Make sure you have the following installed:
- CMake
- A C++ compiler

### Build Steps

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd cursor_elective_counter
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**:
   ```bash
   cmake ..
   ```

4. **Build the project**:
   ```bash
   cmake --build .
   ```

5. **Run the application**:
   ```bash
   ./vote_counter  # On Unix-like systems
   vote_counter.exe  # On Windows
   ```

### GUI Dashboard

The project now includes a modern Qt6-based GUI dashboard with real-time charts, interactive tables, and live updates.

#### Prerequisites
- **Qt6**: Install Qt6 with Core, Widgets, and Charts modules
- **C++17**: Modern C++ compiler support
- **CMake**: Version 3.10 or higher

#### Build Commands

**Windows**:
```batch
build_gui.bat
```

**Linux/macOS**:
```bash
chmod +x build_gui.sh
./build_gui.sh
```

#### GUI Features
- 🎯 **Real-time Dashboard**: Live vote updates with instant results
- 📊 **Interactive Charts**: Bar charts for overall and district results
- 🎮 **User Controls**: Easy election setup and vote input
- 🔧 **Advanced Features**: Auto-refresh, simulation, and export
- 📱 **Responsive Design**: Adapts to different screen sizes

See `GUI_README.md` for detailed GUI usage instructions.

## 🎮 Usage

### Interactive Menu

The application provides an interactive menu with the following options:

1. **Setup Election**: Configure districts and candidates
2. **Start Election**: Begin accepting vote updates
3. **Stop Election**: Stop accepting vote updates
4. **Add Vote Update**: Manually add votes from a precinct
5. **View Current Results**: See overall election results
6. **View District Results**: Get results for a specific district
7. **View Candidate Results**: Get results for a specific candidate
8. **View Election Info**: Display election configuration
9. **Simulate Random Updates**: Test with random vote data
10. **View Vote History**: See all vote updates for audit
11. **Reset Election**: Clear all votes and start over

### Example Workflow

1. **Setup**: Configure your election with districts and candidates
2. **Start**: Begin the election to accept vote updates
3. **Update**: Add votes as they come in from precincts
4. **Monitor**: View real-time results and updates
5. **Audit**: Review vote history for transparency

## 🔧 API Usage

### Basic Example

```cpp
#include "election_system.hpp"

// Create election system
ElectionSystem election("2024 General Election", "November 5, 2024");

// Setup election structure
std::vector<std::string> districts = {"North District", "South District"};
std::vector<std::string> candidates = {"John Smith", "Jane Doe"};
std::vector<std::string> parties = {"Democratic", "Republican"};

election.setupElection(districts, candidates, parties);

// Start election
election.setElectionStatus(true);

// Process vote updates
election.processVoteUpdate("North District", "John Smith", 150, "P001", "timestamp");

// Get results
std::string results = election.getCurrentResults();
std::cout << results;
```

### Performance Characteristics

- **Vote Updates**: O(log n) where n is the number of candidates in a district
- **Result Queries**: O(log n) for district totals, O(d × log n) for overall totals
- **Memory Usage**: O(d × c) where d is districts and c is candidates per district

## 📊 Performance Benchmarks

The system is designed to handle:
- **Small Elections**: < 1,000 candidates (instant results)
- **Medium Elections**: 1,000 - 100,000 candidates (< 1ms updates)
- **Large Elections**: 100,000+ candidates (< 10ms updates)

## 🔒 Security Features

- **Input Validation**: All inputs are validated before processing
- **Audit Trail**: Complete vote history for verification
- **Error Handling**: Graceful error handling with informative messages
- **Data Integrity**: Fenwick Tree ensures accurate vote counting

## 🧪 Testing

The system includes built-in testing capabilities:
- Random vote simulation for stress testing
- Input validation testing
- Performance benchmarking tools

## 📝 License

This project is open source and available under the MIT License.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## 📚 Technical Details

### Fenwick Tree Implementation

The core data structure provides:
- **Efficient Updates**: O(log n) time complexity
- **Fast Queries**: O(log n) range sum queries
- **Memory Efficiency**: Compact representation
- **Scalability**: Handles large datasets efficiently

### Memory Management

- Uses smart pointers for automatic memory management
- Efficient data structures minimize memory overhead
- RAII principles ensure proper resource cleanup

## 🚨 Troubleshooting

### Common Issues

1. **Build Errors**: Ensure you have C++17 support enabled
2. **Runtime Errors**: Check that districts and candidates are properly configured
3. **Performance Issues**: Verify the system meets minimum requirements

### Getting Help

If you encounter issues:
1. Check the error messages for specific details
2. Verify your input data format
3. Ensure the election is properly set up before use

## 🔮 Future Enhancements

Planned features include:
- **Web Interface**: Real-time web dashboard
- **Database Integration**: Persistent storage for large elections
- **API Endpoints**: RESTful API for integration
- **Real-time Streaming**: WebSocket support for live updates
- **Mobile App**: Native mobile applications

## 📞 Support

For support and questions, please open an issue in the repository or contact the development team.

---

**Built with ❤️ for transparent and efficient election management**
