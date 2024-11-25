#include "main.h"
#include "engine.h"

int main(int argc, char *argv[]){

  CEngine* engine = new CEngine();

  engine->Init();

  engine->Start();

  delete engine;

	return 0;
}

void Log(string error){
  fprintf(stderr, "%s", error.c_str());
}
