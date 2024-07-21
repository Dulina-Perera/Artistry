#include <gtk/gtk.h>
#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include "save.hh"

std::vector<unsigned char> capture_frame_buffer(GLFWwindow* window, int width, int height) {
    glfwGetFramebufferSize(window, &width, &height);

    // Ensure the OpenGL context is current
    glfwMakeContextCurrent(window);

    std::vector<unsigned char> pixels(width * height * 4);
    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());

    for (int i = 0; i < height / 2; i++) {
        for (int j = 0; j < width * 4; j++) {
            std::swap(pixels[i * width * 4 + j], pixels[(height - i - 1) * width * 4 + j]);
        }
    }

    return pixels;
}

static void on_save_response(GtkDialog* dialog, int response, gpointer user_data)
{
    auto [width, height, pixels] = *static_cast<std::tuple<int, int, std::vector<unsigned char>*>*>(user_data);

    if (response == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
        g_autoptr(GFile) file = gtk_file_chooser_get_file(chooser);
        g_autofree char* filename = g_file_get_path(file);

        std::string filePath = filename;
        if (filePath.find(".png") == std::string::npos)
        {
            filePath += ".png";
        }

        if (stbi_write_png(filePath.c_str(), width, height, 4, pixels->data(), width * 4))
        {
            g_print("Saved to %s\n", filePath.c_str());
        }
        else
        {
            g_print("Failed to save to %s\n", filePath.c_str());
        }
    }
    gtk_window_destroy(GTK_WINDOW(dialog));
    delete static_cast<std::tuple<int, int, std::vector<unsigned char>*>*>(user_data);
}

void save_as_png(GLFWwindow* window) {
    int width, height;
    std::vector<unsigned char> pixels = capture_frame_buffer(window, width, height);

    gtk_init();

    GtkWidget* dialog;
    GtkFileChooser* chooser;

    dialog = gtk_file_chooser_dialog_new(
        "Save File",
        nullptr,
        GTK_FILE_CHOOSER_ACTION_SAVE,
        "_Cancel",
        GTK_RESPONSE_CANCEL,
        "_Save",
        GTK_RESPONSE_ACCEPT,
        nullptr
    );
    chooser = GTK_FILE_CHOOSER(dialog);

    // Removed the creation of a new window as it is unnecessary and incorrect in GTK4
    // Set the transient parent properly
    gtk_window_set_transient_for(GTK_WINDOW(dialog), nullptr);

    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(dialog), "Untitled.png");

    gtk_window_present(GTK_WINDOW(dialog));

    auto user_data = new std::tuple<int, int, std::vector<unsigned char>*>{width, height, &pixels};
    g_signal_connect(dialog, "response", G_CALLBACK(on_save_response), user_data);
}
