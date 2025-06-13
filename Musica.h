#ifndef MUSICA_H
#define MUSICA_H

#include <string>
#include <iostream>
#include <thread>

#ifdef _WIN32
#include <windows.h>
static PROCESS_INFORMATION pInfo; // GLOBAL para usar en reproducir y detener
#else
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
static pid_t musica_pid = -1;
#endif

inline void reproducirMusica(const std::string& archivo) {
#ifdef _WIN32
    std::string comando = "python player.py \"" + archivo + "\"";
    STARTUPINFOA si = { sizeof(si) };
    // NO vuelvas a declarar pInfo aquí — ya está declarado arriba

    if (!CreateProcessA(
        nullptr,
        (LPSTR)comando.c_str(),
        nullptr, nullptr,
        FALSE,
        CREATE_NO_WINDOW,
        nullptr, nullptr,
        &si, &pInfo)) // usa la global
    {
        std::cerr << "Error al lanzar Python\n";
    }
    else {
        std::cout << "Proceso lanzado correctamente\n";
    }
#else
    musica_pid = fork();
    if (musica_pid == 0) {
        execlp("python3", "python3", "player.py", archivo.c_str(), NULL);
        std::exit(1);
    }
#endif
}

inline void detenerMusica() {
#ifdef _WIN32
    TerminateProcess(pInfo.hProcess, 0);
    CloseHandle(pInfo.hProcess);
    CloseHandle(pInfo.hThread);
#else
    if (musica_pid > 0) {
        kill(musica_pid, SIGTERM);
    }
#endif
}

#endif // MUSICA_H
