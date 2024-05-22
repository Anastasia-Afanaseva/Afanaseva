#pragma once
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

void dostuff(int sock);
void error(const char *msg);
void print_users();
int summ(int a, int b);
int substr(int a, int b);
int multipli(int a, int b);
float division(int a, int b);