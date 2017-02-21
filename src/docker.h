//
// Created by Daniel Suo on 2/2/17.
//

#ifndef DOCKER_DOCKER_H
#define DOCKER_DOCKER_H

#define DOCKER_API_VERSION "v1.25"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>

struct buffer {
  char *data;
  size_t size;
};

struct docker {
  CURL *curl;
  char *version;
  struct buffer *buffer;
};

typedef struct docker DOCKER;

DOCKER *docker_init(char *version);
int docker_destroy(DOCKER *docker_client);
char *docker_buffer(DOCKER *docker_client);
CURLcode docker_post(DOCKER *docker_client, char *url, char *data);
CURLcode docker_get(DOCKER *docker_client, char *url);
CURLcode docker_get_archive(DOCKER *docker_client, char *url, char *tarfile);
CURLcode docker_delete(DOCKER *docker_client, char *url);

#endif //DOCKER_DOCKER_H
