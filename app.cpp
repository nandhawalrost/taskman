#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

// Function to list all processes
void ListProcesses() {
    // Take a snapshot of the current processes
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to take snapshot of processes." << std::endl;
        return;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    // Retrieve information about the first process
    if (!Process32First(hSnapshot, &pe)) {
        std::cerr << "Failed to get process information." << std::endl;
        CloseHandle(hSnapshot);
        return;
    }

    // List all processes
    std::cout << "PID\t\tProcess Name" << std::endl;
    std::cout << "------------------------------" << std::endl;
    do {
        std::wcout << pe.th32ProcessID << "\t\t" << pe.szExeFile << std::endl;
    } while (Process32Next(hSnapshot, &pe));

    CloseHandle(hSnapshot);
}

int main() {
    ListProcesses();
    return 0;
}
