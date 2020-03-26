# ```libdocker```: an SDK for the Docker Engine API in C

A minimalist SDK for accessing the [Docker Engine API](https://docs.docker.com/engine/api/) via C.

## Getting started
```libdocker``` depends on ```curl```, which can be installed easily via most package managers or [from source](https://curl.haxx.se/docs/install.html). A typical workflow:

- ```docker_init``` initializes a UNIX socket connection to the Docker Engine
- ```docker_post``` and ```docker_get``` send requests to the Docker Engine REST API
- ```docker_buffer``` gets response data
- ```docker_destroy``` destroys docker object and frees any associated memory

## Building the Code
- Run the compile script to build the code. By default the example will be part of the build process. ( If anybody wants to not build the example,
 they can manually edit the base CMakeLists. In future, the compile script will accomodate the option.)
- If the build is successful, then a deb package will be created in the build directory. Use the command ```sudo dpkg -i <deb package name>```
to install the package.
- This will add libdocker.so to the /usr/lib directory and the example executable docker_example in /usr/bin
- Also this will add the docker.h header file to /usr/include. If anybody wants to just use the library for dev purpose, they can include it directly.
- Use the sudo command to run the executable created.
- To remove the package ( i.e. the .so file, the docker.h header and the example executable in future ), use the command ```sudo dpkg -r docker_c_sdk```

The library is pretty low-level for now (i.e., doesn't support parsing ```JSON``` responses or have any functions higher-level than ```post``` or ```get```). An example application:

## Multi-threaded applications
Should be fine, but be sure to have a look at ```curl```'s page on the subject (link [here](https://curl.haxx.se/libcurl/c/threadsafe.html)).
