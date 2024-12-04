#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <gtk/gtk.h>

#define MAX_PASS_LENGTH 12
#define true 1
#define false 0

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
char digits[] = "123456789@$&^?![]{}";
int aplphabet_size = sizeof(alphabet) / sizeof(char);
int digit_size = sizeof(digits) / sizeof(char);

GtkWidget *window;
GtkWidget *button;
GtkWidget *input;
GtkWidget *box;

void generate_password();

static void activate(GtkApplication *app, gpointer user_data)
{
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Генератор Паролей");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 120);

    input = gtk_entry_new();
    gtk_entry_set_alignment(input, 0.5);

    button = gtk_button_new_with_label("Сгенерировать");
    g_signal_connect(button, "clicked", G_CALLBACK(generate_password), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    gtk_box_pack_start(GTK_BOX(box), input, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), box);

    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    setlocale(LC_ALL, "");

    GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

// Генерация пароля
void generate_password()
{
    char password[MAX_PASS_LENGTH];
    char symb;
    char digit = '?';

    for (int i = 0; i <= MAX_PASS_LENGTH; i++)
    {
        if (i == MAX_PASS_LENGTH)
        {
            password[i] = '\0';
            break;
        }
        symb = alphabet[0 + rand() % (aplphabet_size - 1)];
        password[i] = symb;
    }

    for (int i = 0; i <= MAX_PASS_LENGTH; i++)
    {
        digit = digits[0 + rand() % (digit_size - 1)];
        password[0 + rand() % MAX_PASS_LENGTH - 1] = digit;
    }

    gtk_entry_set_text(input, password);
}
