#include "election_system.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

void printMenu() {
    std::cout << "\n=== LIVE ELECTION VOTE COUNTER ===\n";
    std::cout << "1. Setup Election\n";
    std::cout << "2. Start Election\n";
    std::cout << "3. Stop Election\n";
    std::cout << "4. Add Vote Update\n";
    std::cout << "5. View Current Results\n";
    std::cout << "6. View District Results\n";
    std::cout << "7. View Candidate Results\n";
    std::cout << "8. View Election Info\n";
    std::cout << "9. Simulate Random Updates\n";
    std::cout << "10. View Vote History\n";
    std::cout << "11. Reset Election\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ElectionSystem election("2024 General Election", "November 5, 2024");
    
    std::cout << "Welcome to the Live Election Vote Counter!\n";
    std::cout << "This system provides O(log n) vote updates and instant aggregated results.\n\n";
    
    int choice;
    bool electionSetup = false;
    
    do {
        printMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                clearScreen();
                std::cout << "=== SETUP ELECTION ===\n\n";
                
                if (electionSetup) {
                    std::cout << "Election is already set up. Reset first if you want to change.\n";
                    waitForEnter();
                    break;
                }
                
                std::vector<std::string> districtNames, candidateNames, partyNames;
                
                // Get districts
                std::cout << "Enter number of districts: ";
                int numDistricts;
                std::cin >> numDistricts;
                std::cin.ignore();
                
                for (int i = 0; i < numDistricts; ++i) {
                    std::string districtName;
                    std::cout << "Enter district " << (i + 1) << " name: ";
                    std::getline(std::cin, districtName);
                    districtNames.push_back(districtName);
                }
                
                // Get candidates
                std::cout << "\nEnter number of candidates: ";
                int numCandidates;
                std::cin >> numCandidates;
                std::cin.ignore();
                
                for (int i = 0; i < numCandidates; ++i) {
                    std::string candidateName, partyName;
                    std::cout << "Enter candidate " << (i + 1) << " name: ";
                    std::getline(std::cin, candidateName);
                    std::cout << "Enter party for " << candidateName << ": ";
                    std::getline(std::cin, partyName);
                    candidateNames.push_back(candidateName);
                    partyNames.push_back(partyName);
                }
                
                try {
                    election.setupElection(districtNames, candidateNames, partyNames);
                    electionSetup = true;
                    std::cout << "\nElection setup completed successfully!\n";
                } catch (const std::exception& e) {
                    std::cout << "\nError setting up election: " << e.what() << "\n";
                }
                
                waitForEnter();
                break;
            }
            
            case 2: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    election.setElectionStatus(true);
                    std::cout << "Election started! Vote updates are now being accepted.\n";
                }
                waitForEnter();
                break;
            }
            
            case 3: {
                clearScreen();
                election.setElectionStatus(false);
                std::cout << "Election stopped. No more vote updates will be accepted.\n";
                waitForEnter();
                break;
            }
            
            case 4: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else if (!election.isElectionActive()) {
                    std::cout << "Election is not active. Start the election first!\n";
                } else {
                    std::cout << "=== ADD VOTE UPDATE ===\n\n";
                    
                    std::string districtName, candidateName, precinctId;
                    int64_t voteCount;
                    
                    std::cin.ignore();
                    std::cout << "Enter district name: ";
                    std::getline(std::cin, districtName);
                    std::cout << "Enter candidate name: ";
                    std::getline(std::cin, candidateName);
                    std::cout << "Enter vote count: ";
                    std::cin >> voteCount;
                    std::cin.ignore();
                    std::cout << "Enter precinct ID: ";
                    std::getline(std::cin, precinctId);
                    
                    if (election.processVoteUpdate(districtName, candidateName, voteCount, precinctId)) {
                        std::cout << "\nVote update processed successfully!\n";
                    } else {
                        std::cout << "\nFailed to process vote update. Check district and candidate names.\n";
                    }
                }
                waitForEnter();
                break;
            }
            
            case 5: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    std::cout << election.getCurrentResults();
                }
                waitForEnter();
                break;
            }
            
            case 6: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    std::string districtName;
                    std::cin.ignore();
                    std::cout << "Enter district name: ";
                    std::getline(std::cin, districtName);
                    std::cout << election.getDistrictResults(districtName);
                }
                waitForEnter();
                break;
            }
            
            case 7: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    std::string candidateName;
                    std::cin.ignore();
                    std::cout << "Enter candidate name: ";
                    std::getline(std::cin, candidateName);
                    std::cout << election.getCandidateResults(candidateName);
                }
                waitForEnter();
                break;
            }
            
            case 8: {
                clearScreen();
                std::cout << election.getElectionInfo();
                waitForEnter();
                break;
            }
            
            case 9: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else if (!election.isElectionActive()) {
                    std::cout << "Election is not active. Start the election first!\n";
                } else {
                    std::cout << "=== SIMULATE RANDOM UPDATES ===\n\n";
                    std::cout << "Enter number of random updates to simulate: ";
                    int numUpdates;
                    std::cin >> numUpdates;
                    
                    if (numUpdates > 0) {
                        election.simulateRandomUpdates(numUpdates);
                        std::cout << "\nSimulated " << numUpdates << " random vote updates.\n";
                    }
                }
                waitForEnter();
                break;
            }
            
            case 10: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    auto history = election.getVoteHistory();
                    std::cout << "=== VOTE HISTORY ===\n\n";
                    
                    if (history.empty()) {
                        std::cout << "No votes have been cast yet.\n";
                    } else {
                        for (const auto& update : history) {
                            std::cout << "[" << update.timestamp << "] "
                                     << update.districtId << " -> "
                                     << update.candidateId << ": +"
                                     << update.voteCount << " votes (Precinct: " << update.precinctId << ")\n";
                        }
                        std::cout << "\nTotal updates: " << history.size() << "\n";
                    }
                }
                waitForEnter();
                break;
            }
            
            case 11: {
                clearScreen();
                if (!electionSetup) {
                    std::cout << "Please setup the election first!\n";
                } else {
                    std::cout << "Are you sure you want to reset the election? (y/n): ";
                    char confirm;
                    std::cin >> confirm;
                    if (confirm == 'y' || confirm == 'Y') {
                        election.resetElection();
                        std::cout << "Election has been reset. All votes cleared.\n";
                    }
                }
                waitForEnter();
                break;
            }
            
            case 0:
                std::cout << "\nThank you for using the Live Election Vote Counter!\n";
                break;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
                waitForEnter();
                break;
        }
        
    } while (choice != 0);
    
    return 0;
}
