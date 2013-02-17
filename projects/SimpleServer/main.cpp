#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include "connectivity.hpp"
#include "Renderer.h"

namespace constants {
    const int bufferSize = 512;
};



void copyArrays(char *dst, char *src, int count, int offset) {
    dst = dst + offset;
    for (int i = 0; i < count; i++) {
        *dst = *src;
        dst++;
        src++;
    }
}

bool saveToFile(const char *filename, char *data, int size) {
    printf("Saving to file %s\n", filename);

    FILE *f = fopen(filename, "w");
    if (f != NULL) {
        fwrite(data, size, sizeof (char), f);
        fclose(f);
        return true;
    }
    return false;
}

bool sendFile(int fd, const char* filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        return false;
    }

    printf("Sending file %s\n", filename);
    fseek(f, 0, SEEK_END);
    int fileSize = ftell(f);
    rewind(f);
    printf("File size = %d\n", fileSize);

    writeInt(fd, fileSize);
    int checkSum = readInt(fd);
    if (checkSum != (int) ceil((double) fileSize / (double) constants::bufferSize)) {
        printf("Checksum not right.\n");
        return false;
    }

    char buffer[constants::bufferSize];
    int n;
    while ((n = fread(buffer, sizeof (char), constants::bufferSize, f)) > 0) {
        write(fd, buffer, n);
        printf("%d bytes ", n);
    }
    fclose(f);

    printf("\n");
    return true;
}

void genRandom(char *s, const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof (alphanum) - 1)];
    }

    s[len] = 0;
}

void handleClient(int fd) {
    int n;
    char initChar = ' ';

    initChar = readChar(fd, ' ');
    if (initChar != '#') {
        close(fd);
        return;
    }

    writeInt(fd, constants::bufferSize);

    int xmlSize = -1;
    xmlSize = readInt(fd, -1);
    printf("Read xml size = %d\n.", xmlSize);

    int numPackets = (int) ceil((double) xmlSize / (double) constants::bufferSize);
    writeInt(fd, numPackets);
    printf("Num packets = %d\n.", numPackets);

    char data[xmlSize];
    char buffer[constants::bufferSize];
    int i = 0;
    while ((n = read(fd, &buffer, constants::bufferSize)) > 0) {
        if (n <= 0) {
            break;
        }

        copyArrays(data, buffer, n, i);
        i += n;
        printf("Read %d bytes. Collected = %d\n", n, i);
        if (i == xmlSize) {
            break;
        }
    }

    printf("Read done.\n");
    char xmlFileName[65];
    char imageFileName[65];

    genRandom((char*) xmlFileName, 60);
    genRandom((char*) imageFileName, 60);
    xmlFileName[60] = '.';
    xmlFileName[61] = 'x';
    xmlFileName[62] = 'm';
    xmlFileName[63] = 'l';
    xmlFileName[64] = '\0';

    imageFileName[60] = '.';
    imageFileName[61] = 'j';
    imageFileName[62] = 'p';
    imageFileName[63] = 'g';
    imageFileName[64] = '\0';

    saveToFile(xmlFileName, data, xmlSize);
    render(xmlFileName, imageFileName);
    sendFile(fd, (char*) imageFileName);

    unlink((char*) xmlFileName);
    unlink((char*) imageFileName);

    close(fd);
    return;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Port not specified.\n");
        exit(0);
    }

    int port = atoi(argv[1]);
    char sendBuff[1025];
    memset(sendBuff, '0', sizeof (sendBuff));
    Addr addr;
    addr.initHost(port);
    Host host;
    host.initByAddr(addr);

    while (1) {
        Connection connfd = host.waitForClient();

        int pid = fork();
        if (pid == 0) {
            printf("I am child. Handling client.\n");
            handleClient(connfd);
            printf("Client handled.\n");
            return 0;
        } else {
            printf("I am parent.");
        }
    }
}
