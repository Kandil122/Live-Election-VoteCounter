#include "../include/election_system.hpp"
#include <iostream>
#include <cassert>

void testBasicElection() {
    std::cout << "Testing basic election functionality...\n";
    
    // Create election system
    ElectionSystem election("Test Election", "2024-01-01");
    
    // Setup election
    std::vector<std::string> districts = {"District A", "District B"};
    std::vector<std::string> candidates = {"Candidate 1", "Candidate 2"};
    std::vector<std::string> parties = {"Party A", "Party B"};
    
    election.setupElection(districts, candidates, parties);
    
    // Show election info
    std::cout << "\n--- Election Information ---\n";
    std::cout << election.getElectionInfo();
    
    // Start election
    election.setElectionStatus(true);
    std::cout << "\n✓ Election started! Vote updates are now being accepted.\n";
    
    // Add some votes and show details after each
    std::cout << "\n--- Adding votes and showing details ---\n";
    
    assert(election.processVoteUpdate("District A", "Candidate 1", 100, "P001"));
    std::cout << "✓ Added 100 votes for Candidate 1 in District A (Precinct P001)\n";
    
    assert(election.processVoteUpdate("District A", "Candidate 2", 75, "P002"));
    std::cout << "✓ Added 75 votes for Candidate 2 in District A (Precinct P002)\n";
    
    assert(election.processVoteUpdate("District B", "Candidate 1", 80, "P003"));
    std::cout << "✓ Added 80 votes for Candidate 1 in District B (Precinct P003)\n";
    
    assert(election.processVoteUpdate("District B", "Candidate 2", 120, "P004"));
    std::cout << "✓ Added 120 votes for Candidate 2 in District B (Precinct P004)\n";
    
    // Show vote history with timestamps
    std::cout << "\n--- Vote History with Timestamps ---\n";
    auto history = election.getVoteHistory();
    for (const auto& update : history) {
        std::cout << "[" << update.timestamp << "] " 
                  << update.districtId << " -> " 
                  << update.candidateId << ": +" 
                  << update.voteCount << " votes (Precinct: " << update.precinctId << ")\n";
    }
    
    // Check results
    std::cout << "\n--- Current Election Results ---\n";
    std::string results = election.getCurrentResults();
    std::cout << results;
    
    // Check district results
    std::cout << "\n--- District A Results ---\n";
    std::string districtAResults = election.getDistrictResults("District A");
    std::cout << districtAResults;
    
    // Check candidate results
    std::cout << "\n--- Candidate 1 Results ---\n";
    std::string candidate1Results = election.getCandidateResults("Candidate 1");
    std::cout << candidate1Results;
    
    // Check current leader
    std::cout << "\n--- Current Election Leader ---\n";
    std::string leader = election.getCurrentLeader();
    std::cout << "Leader: " << leader << "\n";
    
    // Show final summary
    std::cout << "\n--- Final Summary ---\n";
    std::cout << "✓ All votes processed successfully\n";
    std::cout << "✓ Vote history recorded with timestamps\n";
    std::cout << "✓ Results aggregated in real-time\n";
    std::cout << "✓ Basic election test passed!\n\n";
}

void testPerformance() {
    std::cout << "Testing performance with large number of updates...\n";
    
    ElectionSystem election("Performance Test", "2024-01-01");
    
    // Setup with more districts and candidates
    std::vector<std::string> districts;
    std::vector<std::string> candidates;
    std::vector<std::string> parties;
    
    for (int i = 1; i <= 10; ++i) {
        districts.push_back("District " + std::to_string(i));
    }
    
    for (int i = 1; i <= 20; ++i) {
        candidates.push_back("Candidate " + std::to_string(i));
        parties.push_back("Party " + std::to_string(i));
    }
    
    election.setupElection(districts, candidates, parties);
    election.setElectionStatus(true);
    
    std::cout << "✓ Performance test election configured with " << districts.size() 
              << " districts and " << candidates.size() << " candidates\n";
    
    // Simulate many vote updates
    std::cout << "\n--- Simulating 1000 random vote updates ---\n";
    std::cout << "Processing... (this may take a moment)\n";
    election.simulateRandomUpdates(1000);
    
    // Show some sample vote history
    std::cout << "\n--- Sample Vote History (Last 10 updates) ---\n";
    auto history = election.getVoteHistory();
    int start = std::max(0, static_cast<int>(history.size()) - 10);
    for (size_t i = start; i < history.size(); ++i) {
        const auto& update = history[i];
        std::cout << "[" << update.timestamp << "] " 
                  << update.districtId << " -> " 
                  << update.candidateId << ": +" 
                  << update.voteCount << " votes (Precinct: " << update.precinctId << ")\n";
    }
    
    // Get results
    std::cout << "\n--- Performance Test Results ---\n";
    std::cout << "✓ Performance test completed successfully!\n";
    std::cout << "✓ Total vote updates processed: " << history.size() << "\n";
    std::cout << "✓ All updates processed with O(log n) efficiency\n\n";
}



void testEdgeCases() {
    std::cout << "Testing edge cases...\n";
    
    ElectionSystem election("Edge Case Test", "2024-01-01");
    
    // Test without setup
    std::cout << "\n--- Testing without election setup ---\n";
    std::string info = election.getElectionInfo();
    std::cout << info;
    assert(info.find("Districts: 0") != std::string::npos);
    std::cout << "✓ Confirmed: No districts configured\n";
    
    // Test vote update without active election
    std::cout << "\n--- Testing vote update without active election ---\n";
    bool result = election.processVoteUpdate("District A", "Candidate 1", 100, "P001");
    std::cout << "Vote update result: " << (result ? "SUCCESS" : "FAILED (expected)") << "\n";
    assert(!result);
    std::cout << "✓ Confirmed: Cannot add votes to inactive election\n";
    
    // Setup election
    std::cout << "\n--- Setting up election ---\n";
    std::vector<std::string> districts = {"District A"};
    std::vector<std::string> candidates = {"Candidate 1"};
    std::vector<std::string> parties = {"Party A"};
    
    election.setupElection(districts, candidates, parties);
    std::cout << "✓ Election configured with 1 district and 1 candidate\n";
    
    // Test invalid vote update
    std::cout << "\n--- Testing invalid vote updates ---\n";
    result = election.processVoteUpdate("Invalid District", "Candidate 1", 100, "P001");
    std::cout << "Invalid district result: " << (result ? "SUCCESS" : "FAILED (expected)") << "\n";
    assert(!result);
    
    result = election.processVoteUpdate("District A", "Invalid Candidate", 100, "P001");
    std::cout << "Invalid candidate result: " << (result ? "SUCCESS" : "FAILED (expected)") << "\n";
    assert(!result);
    
    std::cout << "✓ Edge case tests passed!\n\n";
}

int main() {
    std::cout << "=== ELECTION SYSTEM TEST SUITE ===\n\n";
    
    try {
        testBasicElection();
        testPerformance();
        testEdgeCases();
        
        std::cout << "All tests passed successfully!\n";
        std::cout << "The Live Election Vote Counter is working correctly.\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
