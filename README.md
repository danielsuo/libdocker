# ```libdocker```: an SDK for the Docker Engine API in C

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

The example above shown can be run as follows for a quick test on your environment setup
```
gcc test.c ./src/docker.c -o test -std=c99 -lcurl -I ./src
./test
```


## Adding as CMake subdirectory dependency
Add the following lines to your ```CMakeLists.txt```.
```
# Let's say the libdocker directory is lib/libdocker
set(LIBDOCKER_DIR lib/libdocker)

# Add subdirectory to compile the static library
add_subdirectory(${LIBDOCKER_DIR})

# Make sure CMake knows where the header files are
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/${LIBDOCKER_DIR}/${DOCKER_INCLUDE_DIR}
)

# Link in the static library
target_link_libraries(
    ${PROJECT_NAME}
    docker
)
```

## Multi-threaded applications
Should be fine, but be sure to have a look at ```curl```'s page on the subject (link [here](https://curl.haxx.se/libcurl/c/threadsafe.html)).
