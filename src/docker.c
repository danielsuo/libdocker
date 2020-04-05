//
// Created by Daniel Suo on 2/2/17.
//

#include "docker.h"

void malloc_fail() {
  fprintf(stderr, "ERROR: Failed to allocate memory. Committing seppuku.");
  exit(-1);
}

static size_t write_function(void *data, size_t size, size_t nmemb, void *buffer) {
  size_t realsize = size * nmemb;
  struct buffer *mem = (struct buffer *)buffer;

  mem->data = realloc(mem->data, mem->size + realsize + 1);
  if(mem->data == NULL) {
    malloc_fail();
  }

  memcpy(&(mem->data[mem->size]), data, realsize);
  mem->size += realsize;
  mem->data[mem->size] = 0;

  return realsize;
}

void init_buffer(DOCKER *client) {
  client->buffer->data = (char *) malloc(1);
  client->buffer->size = 0;
}

void init_curl(DOCKER *client) {
  curl_easy_setopt(client->curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
  curl_easy_setopt(client->curl, CURLOPT_WRITEFUNCTION, write_function);
  curl_easy_setopt(client->curl, CURLOPT_WRITEDATA, client->buffer);
}

CURLcode perform(DOCKER *client, char *url) {
  init_buffer(client);
  curl_easy_setopt(client->curl, CURLOPT_URL, url);
  CURLcode response = curl_easy_perform(client->curl);
  curl_easy_reset(client->curl);

  return response;
}

DOCKER *docker_init(char *version) {
  size_t version_len = strlen(version);

  if (version_len < 5) {
    fprintf(stderr, "WARNING: version malformed.");
    return NULL;
  }

  DOCKER *client = (DOCKER *) malloc(sizeof(struct docker));

  client->buffer = (struct buffer *) malloc(sizeof(struct buffer));


  client->version = (char *) malloc(sizeof(char) * version_len);
  if (client->version == NULL) {
    malloc_fail();
  }

  memcpy(client->version, version, version_len);

  client->curl = curl_easy_init();

  if (client->curl) {
    init_curl(client);
    return client;
  }

  return NULL;
}

int docker_destroy(DOCKER *client) {
  curl_easy_cleanup(client->curl);
  free(client->buffer->data);
  free(client->buffer);
  free(client->version);
  free(client);
  client = NULL;

  return 0;
}

char *docker_buffer(DOCKER *client) {
  return client->buffer->data;
}

CURLcode docker_post(DOCKER *client, char *url, char *data) {
  init_curl(client);

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Content-Type: application/json");
  curl_easy_setopt(client->curl, CURLOPT_HTTPHEADER, headers);
  curl_easy_setopt(client->curl, CURLOPT_POSTFIELDS, (void *)data);
  CURLcode response = perform(client, url);
  curl_slist_free_all(headers);

  return response;
}

CURLcode docker_get(DOCKER *client, char *url) {
  init_curl(client);
  return perform(client, url);
}

