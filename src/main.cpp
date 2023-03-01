
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <sched.h>
#include <unistd.h>

#include "mem.h"
#include "config.h"

pid_t GetPIDFromProcessName(const char *process_name) {
  char cmd[256];
  // Create a command to run in the shell, which will list all running processes
  // and filter out the process with the specified name using grep.

  // Modifed the following ling to only get the second PID, which is the one for
  // the actual game.
  snprintf(cmd, sizeof(cmd), "ps -e | grep -m1 %s", process_name);

  // Open a pipe to run the command and read its output.
  FILE *pipe = popen(cmd, "r");
  if (!pipe) {
    // If the pipe couldn't be opened, return an error code (-1).
    return -1;
  }

  // Read the first line of the output from the pipe.
  char line[256];
  fgets(line, sizeof(line), pipe);

  // Close the pipe.
  pclose(pipe);

  // If no output was produced by the command, return an error code (-1).
  if (strlen(line) == 0) {
    return -1;
  }

  // Parse the PID from the first token in the output line.
  char *pid_str = strtok(line, " ");
  if (!pid_str) {
    // If no token was found, return an error code (-1).
    return -1;
  }

  // Convert the PID string to an integer and return it.
  return atoi(pid_str);
}

void UpdateLights(float health) {
  // Make the float into an int, because the Python script only accepts int values.
  int healthAsInt = std::floor(health);

  char command[106];
  
  // This runs the Python script as the user who is currently logged in.
  snprintf(command, sizeof(command),"sudo -u $(logname) python python/set_lights_based_on_health.py %d", healthAsInt);
  system(command);
}

float GetHealthAsPercentage(float health, float max_health) {
  return (health / max_health) * 100.0f;
}

void PrintValuesToConsole(pid_t processID, float currentHealth, float lastHealthRegistered){
  system("clear");
  printf("ProcessID: %d\n", processID);
  printf("Health: %f\n", currentHealth);
  printf("lastHealthRegistered: %f\n", lastHealthRegistered);
}

int main() {
  pid_t processID = GetPIDFromProcessName(Config::processName.c_str());

  // Health Address, for Saints Row 3 this is static.
  uintptr_t healthAddress = 0x05686410;

  float currentHealth;
  float lastHealthRegistered = 0.0f;
  float maxHealth = 2000.0f;

  // Open the event controlling the keyboard, so we can check keypresses.
  int fd = open(Config::keyboardEvent.c_str(), O_RDONLY);
  if (fd < 0) {
    std::cerr << ("Failed to open keyboard device. Try running with sudo?");
    return 1;
  }
  
  // Monitor keyboard events.
  struct input_event ev;
  bool exitKeyPressed = false;

  while (!exitKeyPressed) {

    // Check for the HACK_EXITKEY pressed.
    if (ev.type == EV_KEY && ev.value == 0) {
      if (ev.code == Config::Keybinds::HACK_EXITKEY) {
        exitKeyPressed = true;
        printf("Exiting now...");
        continue;
      }
    }

    // Read health memory.
    mem::ReadProcessMemory(processID, (void *)healthAddress, &currentHealth,sizeof(currentHealth));

    if (currentHealth != lastHealthRegistered) {
      // This function is here just to keep the code cleaner, I could just put all of the printf statements here.
      PrintValuesToConsole(processID, currentHealth, lastHealthRegistered);

      lastHealthRegistered = currentHealth;

      // Update my Desk Lights colour to reflect our health.
      UpdateLights(GetHealthAsPercentage(currentHealth, maxHealth));
    }

    usleep(175);
  }

  return 0;
}