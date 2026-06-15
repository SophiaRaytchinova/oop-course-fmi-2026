#include "AccountRepository.h"
#include "AuthenticationContext.h"
#include "BankService.h"
#include "CommandFactory.h"
#include "TransactionRepository.h"
#include "UserRepository.h"

#include <exception>
#include <iostream>
#include <memory>
#include <string>

int main() {
    auto userRepository = std::make_shared<UserRepository>("./users.txt");
    auto accountRepository = std::make_shared<AccountRepository>("./accounts.txt");
    auto transactionRepository = std::make_shared<TransactionRepository>("./transactions.txt");

    // load data into vectors from text files at the beginning of the program
    userRepository->load();
    accountRepository->load();
    transactionRepository->load();

    auto authenticationContext =
        std::make_shared<AuthenticationContext>(userRepository);

    auto bankService = std::make_shared<BankService>(
        accountRepository,
        transactionRepository
    );

    CommandFactory commandFactory(authenticationContext, bankService);

    std::string input;

    while (true) {
        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input == "exit") {
            // or maybe create an ExitCommand if you want, but that way is easier
            break;
        }

        try {
            auto command = commandFactory.create(input);
            CommandResponse response = command->execute();
            std::cout << response.getMessage() << '\n';
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    // saving the changes to files once the program finishes...
    userRepository->save();
    accountRepository->save();
    transactionRepository->save();

    return 0;
}
