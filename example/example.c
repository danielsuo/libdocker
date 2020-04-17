#include <stdio.h>
#include "docker.h"


int main() 
{
  DOCKER *docker = docker_init("v1.25");
  CURLcode response;

  if (docker)
  {
    printf("The following are the Docker images present in the system.\n");
    response = docker_get(docker, "http://v1.25/images/json");
    if (response == CURLE_OK)
    {
      fprintf(stderr, "%s\n", docker_buffer(docker));
    }

    docker_destroy(docker);
  } 
  else 
  {
    fprintf(stderr, "ERROR: Failed to get get a docker client!\n");
  }

  return 0;
}
