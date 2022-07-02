// Final state machine that validates that the input is dividable by 3
// Copyright (C) 2022  jUnG3@users.noreply.github.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum allowed_state
{
    S, // Start state and allowed state
       // S -> J for: 1,4,7; S -> D for: 2,5,8; S -> S for: 0,3,6,9
    J, // J -> D for: 1,4,7; J -> S for: 2,5,8; J -> J for: 0,3,6,9
    D  // D -> S for: 1,4,7; D -> J for: 2,5,8; D -> D for: 0,3,6,9
};

typedef enum allowed_state allowed_state_t;

static inline allowed_state_t
do_transition(allowed_state_t current_state, char next_symbol)
{
    u_int8_t divide_result = (next_symbol - 48) % 3;
    if (current_state == S && divide_result == 0) {
        return S;
    }
    if (current_state == S && divide_result == 1) {
        return J;
    }
    if (current_state == S && divide_result == 2) {
        return D;
    }
    if (current_state == J && divide_result == 0) {
        return J;
    }
    if (current_state == J && divide_result == 1) {
        return D;
    }
    if (current_state == J && divide_result == 2) {
        return S;
    }
    if (current_state == D && divide_result == 0) {
        return D;
    }
    if (current_state == D && divide_result == 1) {
        return S;
    }
    if (current_state == D && divide_result == 2) {
        return J;
    }
}

static inline bool
is_acceptable(allowed_state_t current_state)
{
    return current_state == S;
}

static inline bool
is_num(char c)
{
    return c >= '0' && c <= '9';
}

int
main()
{
    u_int16_t number_of_chars = 1024;
    char* buffer = malloc(sizeof(char) * number_of_chars);
    if (buffer == NULL) {
        fprintf(stderr,
                "Could not allocate buffer for %d characters.\n",
                number_of_chars);
        perror("malloc");
        return EXIT_FAILURE;
    }
    allowed_state_t current_state = S;
    bool system_state = true;
    bool machine_finished = false;
    do {
        ssize_t number_of_bytes_read =
          read(STDIN_FILENO, buffer, number_of_chars);
        if (number_of_bytes_read == -1) {
            free(buffer);
            fprintf(stderr, "Error while reading from standard input\n");
            perror("read");
            return EXIT_FAILURE;
        }
        for (u_int16_t i = 0; i < number_of_chars; ++i) {
            if (buffer[i] == '\n') {
                machine_finished = true;
                break;
            }
            if (is_num(buffer[i])) {
                current_state = do_transition(current_state, buffer[i]);
                system_state = is_acceptable(current_state);
            } else {
                system_state = false;
                machine_finished = true;
                break;
            }
        }
    } while (!machine_finished);
    if (system_state) {
        printf("The given input is accepted.\n");
    } else {
        printf("The given input is not accepted.\n");
    }
    free(buffer);
    return EXIT_SUCCESS;
}
