#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void type_string(const char* str) 
{
    for (int i = 0; str[i] != '\0'; i++) 
    {
        char c = str[i];
        
        if (c == '\r') 
        {
            continue;
        }
        
        if (c == '\n') 
        {
            SHORT vk_slash = VkKeyScanA('/');
            UINT vkey_slash = LOBYTE(vk_slash);
            BOOLEAN shift_slash = HIBYTE(vk_slash) & 1;

            INPUT slash_inputs[4];
            ZeroMemory(slash_inputs, sizeof(slash_inputs));
            int s_count = 0;

            if (shift_slash) 
            {
                slash_inputs[s_count].type = INPUT_KEYBOARD;
                slash_inputs[s_count].ki.wVk = VK_SHIFT;
                s_count++;
            }

            slash_inputs[s_count].type = INPUT_KEYBOARD;
            slash_inputs[s_count].ki.wVk = vkey_slash;
            s_count++;

            slash_inputs[s_count].type = INPUT_KEYBOARD;
            slash_inputs[s_count].ki.wVk = vkey_slash;
            slash_inputs[s_count].ki.dwFlags = KEYEVENTF_KEYUP;
            s_count++;

            if (shift_slash) 
            {
                slash_inputs[s_count].type = INPUT_KEYBOARD;
                slash_inputs[s_count].ki.wVk = VK_SHIFT;
                slash_inputs[s_count].ki.dwFlags = KEYEVENTF_KEYUP;
                s_count++;
            }

            SendInput(s_count, slash_inputs, sizeof(INPUT));
            Sleep(20);

            INPUT bs_inputs[2];
            ZeroMemory(bs_inputs, sizeof(bs_inputs));
            bs_inputs[0].type = INPUT_KEYBOARD;
            bs_inputs[0].ki.wVk = VK_BACK;
            bs_inputs[1].type = INPUT_KEYBOARD;
            bs_inputs[1].ki.wVk = VK_BACK;
            bs_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(2, bs_inputs, sizeof(INPUT));
            Sleep(20);

            INPUT enter_inputs[2];
            ZeroMemory(enter_inputs, sizeof(enter_inputs));
            enter_inputs[0].type = INPUT_KEYBOARD;
            enter_inputs[0].ki.wVk = VK_RETURN;
            enter_inputs[1].type = INPUT_KEYBOARD;
            enter_inputs[1].ki.wVk = VK_RETURN;
            enter_inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(2, enter_inputs, sizeof(INPUT));
            
            Sleep(50);
            continue;
        }

        SHORT vk = VkKeyScanA(c);
        if (vk == -1) continue;

        UINT virtual_key = LOBYTE(vk);
        BOOLEAN shift_pressed = HIBYTE(vk) & 1;

        INPUT inputs[4];
        ZeroMemory(inputs, sizeof(inputs));
        int input_count = 0;

        if (shift_pressed) {
            inputs[input_count].type = INPUT_KEYBOARD;
            inputs[input_count].ki.wVk = VK_SHIFT;
            input_count++;
        }

        inputs[input_count].type = INPUT_KEYBOARD;
        inputs[input_count].ki.wVk = virtual_key;
        input_count++;

        inputs[input_count].type = INPUT_KEYBOARD;
        inputs[input_count].ki.wVk = virtual_key;
        inputs[input_count].ki.dwFlags = KEYEVENTF_KEYUP;
        input_count++;

        if (shift_pressed) {
            inputs[input_count].type = INPUT_KEYBOARD;
            inputs[input_count].ki.wVk = VK_SHIFT;
            inputs[input_count].ki.dwFlags = KEYEVENTF_KEYUP;
            input_count++;
        }

        SendInput(input_count, inputs, sizeof(INPUT));
        Sleep(20);
    }
}

int main() {
    const char* filename = "code.txt";

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        system("pause");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* code_to_type = (char*)malloc(length + 1);
    if (code_to_type == NULL) {
        fclose(file);
        return 1;
    }

    size_t read_bytes = fread(code_to_type, 1, length, file);
    code_to_type[read_bytes] = '\0';
    fclose(file);

    printf("Waiting 3 seconds...\n");
    Sleep(3000);

    type_string(code_to_type);

    free(code_to_type);

    printf("\nDone!\n");
    return 0;
}