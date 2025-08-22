#include "../include/election_system.hpp"
#include <iostream>
#include <thread>
#include <chrono>

/**
 * Example demonstrating the Live Election Vote Counter system
 * This shows how to use the system programmatically for automated vote processing
 */
int main() {
    std::cout << "=== SAMPLE ELECTION DEMONSTRATION ===\n\n";
    
    // Create election system
    ElectionSystem election("2024 Presidential Election", "November 5, 2024");
    
    // Setup election with realistic data
    std::vector<std::string> districts = {
        "California", "Texas", "Florida", "New York", "Illinois"
    };
    
    std::vector<std::string> candidates = {
        "John Smith", "Jane Doe", "Bob Johnson", "Alice Wilson"
    };
    
    std::vector<std::string> parties = {
        "Democratic", "Republican", "Independent", "Green"
    };
    
    std::cout << "Setting up election with " << districts.size() << " districts and " 
              << candidates.size() << " candidates...\n";
    
    election.setupElection(districts, candidates, parties);
    
    // Start the election
    election.setElectionStatus(true);
    std::cout << "Election started!\n\n";
    
    // Simulate real-time vote updates from different precincts
    std::cout << "Simulating real-time vote updates...\n";
    
    // California precincts reporting
    election.processVoteUpdate("California", "John Smith", 1250, "CA-P001");
    election.processVoteUpdate("California", "Jane Doe", 980, "CA-P001");
    election.processVoteUpdate("California", "Bob Johnson", 320, "CA-P001");
    
    election.processVoteUpdate("California", "John Smith", 890, "CA-P002");
    election.processVoteUpdate("California", "Jane Doe", 1100, "CA-P002");
    
    // Texas precincts reporting
    election.processVoteUpdate("Texas", "Jane Doe", 1450, "TX-P001");
    election.processVoteUpdate("Texas", "John Smith", 1200, "TX-P001");
    election.processVoteUpdate("Texas", "Bob Johnson", 800, "TX-P001");
    
    // Florida precincts reporting
    election.processVoteUpdate("Florida", "John Smith", 1100, "FL-P001");
    election.processVoteUpdate("Florida", "Jane Doe", 1350, "FL-P001");
    election.processVoteUpdate("Florida", "Alice Wilson", 450, "FL-P001");
    
    // New York precincts reporting
    election.processVoteUpdate("New York", "John Smith", 980, "NY-P001");
    election.processVoteUpdate("New York", "Jane Doe", 1200, "NY-P001");
    election.processVoteUpdate("New York", "Bob Johnson", 600, "NY-P001");
    
    // Illinois precincts reporting
    election.processVoteUpdate("Illinois", "John Smith", 850, "IL-P001");
    election.processVoteUpdate("Illinois", "Jane Doe", 1100, "IL-P001");
    election.processVoteUpdate("Illinois", "Alice Wilson", 380, "IL-P001");
    
    std::cout << "Initial vote updates processed.\n\n";
    
    // Display current results
    std::cout << "=== CURRENT ELECTION RESULTS ===\n";
    std::cout << election.getCurrentResults();
    
    // Simulate more updates coming in
    std::cout << "\nSimulating additional vote updates...\n";
    
    // More California votes
    election.processVoteUpdate("California", "John Smith", 750, "CA-P003");
    election.processVoteUpdate("California", "Jane Doe", 680, "CA-P003");
    
    // More Texas votes
    election.processVoteUpdate("Texas", "Jane Doe", 920, "TX-P002");
    election.processVoteUpdate("Texas", "John Smith", 850, "TX-P002");
    
    // More Florida votes
    election.processVoteUpdate("Florida", "John Smith", 650, "FL-P002");
    election.processVoteUpdate("Florida", "Jane Doe", 720, "FL-P002");
    
    std::cout << "Additional updates processed.\n\n";
    
    // Show updated results
    std::cout << "=== UPDATED ELECTION RESULTS ===\n";
    std::cout << election.getCurrentResults();
    
    // Show specific district results
    std::cout << "\n=== CALIFORNIA DISTRICT RESULTS ===\n";
    std::cout << election.getDistrictResults("California");
    
    // Show specific candidate results
    std::cout << "\n=== JOHN SMITH CANDIDATE RESULTS ===\n";
    std::cout << election.getCandidateResults("John Smith");
    
    // Show current leader
    std::cout << "\n=== CURRENT ELECTION LEADER ===\n";
    std::cout << "Leader: " << election.getCurrentLeader() << "\n";
    
    // Show vote history
    auto history = election.getVoteHistory();
    std::cout << "\n=== VOTE UPDATE HISTORY ===\n";
    std::cout << "Total vote updates processed: " << history.size() << "\n";
    
    // Show last few updates
    std::cout << "\nLast 5 vote updates:\n";
    int start = std::max(0, static_cast<int>(history.size()) - 5);
    for (size_t i = start; i < history.size(); ++i) {
        const auto& update = history[i];
        std::cout << "[" << update.timestamp << "] " 
                  << update.districtId << " -> " 
                  << update.candidateId << ": +" 
                  << update.voteCount << " votes\n";
    }
    
    // Stop the election
    election.setElectionStatus(false);
    std::cout << "\nElection stopped.\n";
    
    std::cout << "\n=== DEMONSTRATION COMPLETED ===\n";
    std::cout << "This example shows how the system can handle:\n";
    std::cout << "- Real-time vote updates from multiple precincts\n";
    std::cout << "- Instant result aggregation across districts\n";
    std::cout << "- Efficient querying at various granularity levels\n";
    std::cout << "- Complete audit trail of all vote updates\n";
    
    return 0;
}
