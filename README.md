# ```libdocker```: a Docker SDK in C

A minimalist SDK for accessing the [Docker Engine API](https://docs.docker.com/engine/api/) via C.

## Getting started
```libdocker``` depends on ```curl```, which can be installed easily via most package managers or [from source](https://curl.haxx.se/docs/install.html). A typical workflow:

- ```docker_init``` initializes a UNIX socket connection to the Docker Engine
- ```docker_post``` and ```docker_get``` send requests to the Docker Engine REST API
- ```docker_buffer``` gets response data
- ```docker_destroy``` destroys docker object and frees any associated memory

The library is pretty low-level for now (i.e., doesn't support parsing ```JSON``` responses or have any functions higher-level than ```post``` or ```get```). An example application:

```
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
```

## Multi-threaded applications
Should be fine, but be sure to have a look at ```curl```'s page on the subject (link [here](https://curl.haxx.se/libcurl/c/threadsafe.html)).