#include "docker.h"



int main() {

    fprintf(stderr, "curl_version: %s\n", curl_version());

      DOCKER *docker = docker_init("v1.25");

        if (docker) {
              CURLcode response = docker_post(docker, "http://v1.25/containers/create",
                                                      "{\"Image\": \"alpine\", \"Cmd\": [\"echo\", \"hello world\"]}");
                  if (response == CURLE_OK) {
                          fprintf(stderr, "%s\n", docker_buffer(docker));
                              }

                      response = docker_get(docker, "http://v1.25/images/json");

                          if (response == CURLE_OK) {
                                  fprintf(stderr, "%s\n", docker_buffer(docker));
                                      }

                              docker_destroy(docker);
                                } else {
                                      fprintf(stderr, "ERROR: Failed to get get a docker client!\n");
                                        }

          return 0;
}
