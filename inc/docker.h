//
// Created by Daniel Suo on 2/2/17.
//

#ifndef DOCKER_DOCKER_H
#define DOCKER_DOCKER_H

#define DOCKER_API_VERSION v1.25

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C"{
#endif

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
CURLcode docker_delete(DOCKER *docker_client, char *url);
CURLcode docker_post(DOCKER *docker_client, char *url, char *data);
CURLcode docker_get(DOCKER *docker_client, char *url);

/**
 * @brief Send a DELETE request to the Docker API and optionally capture the HTTP status code.
 *
 * @param[in] client Docker client context.
 * @param[in] url API endpoint where the request is to be sent.
 * @param[out] out_http_status HTTP status code returned by the API. Accepts NULL for cases when the status code is not desired.
 * @return Curl error code (CURLE_OK on success).
 */
CURLcode docker_delete_with_http_status(DOCKER *docker_client, char *url, long *out_http_status);

/**
 * @brief Send a POST request to the Docker API and optionally capture the HTTP status code.
 *
 * @param[in] client Docker client context.
 * @param[in] url API endpoint where the request is to be sent.
 * @param[in] data POST request body.
 * @param[out] out_http_status HTTP status code returned by the API. Accepts NULL for cases when the status code is not desired.
 * @return Curl error code (CURLE_OK on success).
 */
CURLcode docker_post_with_http_status(DOCKER *docker_client, char *url, char *data, long *out_http_status);

/**
 * @brief Send a GET request to the Docker API and optionally capture the HTTP status code.
 *
 * @param[in] client Docker client context.
 * @param[in] url API endpoint where the request is to be sent.
 * @param[out] out_http_status HTTP status code returned by the API. Accepts NULL for cases when the status code is not desired.
 * @return Curl error code (CURLE_OK on success).
 */
CURLcode docker_get_with_http_status(DOCKER *docker_client, char *url, long *out_http_status);

#ifdef __cplusplus
}
#endif

#endif //DOCKER_DOCKER_H
