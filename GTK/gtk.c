#include <gtk/gtk.h>
#include<gtk-3.0/gtk/gtk.h>
#include "../headers/patients.h"
#include "../headers/doctors.h"
#include "../headers/authentication.h"
#include "../headers/medic.h"
#include "../headers/hospital.h"
#include "../headers/nav.h"
#include "../headers/departments.h"
#include "../headers/queue.h"
#include "../headers/saveLoad.h"
#include "../headers/stack.h"
#include "../headers/linked.h"
#include "../headers/resources.h"
#include "../headers/treeDoc.h"
#include "../headers/treePat.h"
#include "../headers/departments.h"
#include <stdio.h>
#include <stdlib.h>
 
// Function to create the GTK window

GtkWidget* create_window() {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Welcome to the Hospital Management System");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Connect the destroy signal to exit the application
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    return window;
}

void departmentsInfo(GtkWidget *widget, gpointer data);


void departmentsInfo(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;
    char info[1024];

    // Create a dialog window
    dialog = gtk_dialog_new_with_buttons("Department Information",
                                         GTK_WINDOW(gtk_widget_get_toplevel(widget)),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_Close", GTK_RESPONSE_CLOSE, NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Prepare department information
    snprintf(info, sizeof(info), "Departments:\n"
                                  "1. Lab\n"
                                  "2. Cardiology\n"
                                  "3. Physiology\n"
                                  "4. Neurology\n");

    label = gtk_label_new(info);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialog);

    // Connect the response signal to close the dialog
    g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
}
void viewDoctorQueueDialog(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area, *doctor_id_entry, *label, *doctor_rank_entry;
    GtkWindow *parent = NULL;
    if (widget)
        parent = GTK_WINDOW(gtk_widget_get_toplevel(widget));

    dialog = gtk_dialog_new_with_buttons(
        "View Doctor's Queue",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_View", GTK_RESPONSE_ACCEPT,
        "_Cancel", GTK_RESPONSE_REJECT,
        NULL
    );

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    doctor_id_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(doctor_id_entry), "Doctor ID");
    doctor_rank_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(doctor_rank_entry), "Doctor Rank (1-6)");
    gtk_entry_set_width_chars(GTK_ENTRY(doctor_id_entry), 20);
    gtk_entry_set_width_chars(GTK_ENTRY(doctor_rank_entry), 20);

    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Enter Doctor ID:"));
    gtk_container_add(GTK_CONTAINER(content_area), doctor_id_entry);
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Enter Doctor Rank (1-6):"));
    gtk_container_add(GTK_CONTAINER(content_area), doctor_rank_entry);
    label = gtk_label_new("Enter the Doctor ID to view their queue:");

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        const char *doctor_id = gtk_entry_get_text(GTK_ENTRY(doctor_id_entry));
        const char *doctor_rank_str = gtk_entry_get_text(GTK_ENTRY(doctor_rank_entry));
        int doctor_rank = atoi(doctor_rank_str);
        if (doctor_rank < 1 || doctor_rank > 6) {
            label = gtk_label_new("Invalid rank. Please enter a rank between 1 and 6.");
            gtk_container_add(GTK_CONTAINER(content_area), label);
            gtk_widget_show_all(content_area);
            return;
        }
        // Find the doctor by ID (you must implement/find this function)

        doctor *doc = findDocById((char*)doctor_id, doctor_rank ); // adjust rank/department as needed
        if (doc && doc->doctorQueue) {
            // Optionally, redirect displayDoctorSchedule output to a string and show in GTK
            // For now, just call it (prints to terminal)
            displayDoctorSchedule(doc->doctorQueue);

            label = gtk_label_new("Doctor schedule printed to terminal.");
        } else {
            label = gtk_label_new("Doctor not found or no queue.");
        }
        gtk_container_add(GTK_CONTAINER(content_area), label);
        gtk_widget_show_all(content_area);
    }

    gtk_widget_destroy(dialog);
}
void addPatientDialog(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkWidget *name_entry, *age_entry, *medical_case_entry, *address_entry;
    GtkWidget *condition_combo, *department_combo, *assured_check;
    GtkWidget *label;
    GtkWindow *parent = NULL;
    if (widget)
        parent = GTK_WINDOW(gtk_widget_get_toplevel(widget));

    dialog = gtk_dialog_new_with_buttons(
        "Add Patient",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Add", GTK_RESPONSE_ACCEPT,
        "_Cancel", GTK_RESPONSE_REJECT,
        NULL
    );
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Entry fields
    name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Name");
    age_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(age_entry), "Age");
    medical_case_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(medical_case_entry), "Medical Case");
    address_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_entry), "Address");

    // Condition combo box
    condition_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(condition_combo), "Urgence");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(condition_combo), "Danger");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(condition_combo), "Normal");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(condition_combo), "Visit");
    gtk_combo_box_set_active(GTK_COMBO_BOX(condition_combo), 0);

    // Department combo box
    department_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(department_combo), "Lab");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(department_combo), "Cardiology");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(department_combo), "Physiology");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(department_combo), "Neurology");
    gtk_combo_box_set_active(GTK_COMBO_BOX(department_combo), 0);

    // Assurance checkbox
    assured_check = gtk_check_button_new_with_label("Is Assured?");

    // Add widgets to dialog
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Enter Patient Details:"));
    gtk_container_add(GTK_CONTAINER(content_area), name_entry);
    gtk_container_add(GTK_CONTAINER(content_area), age_entry);
    gtk_container_add(GTK_CONTAINER(content_area), medical_case_entry);
    gtk_container_add(GTK_CONTAINER(content_area), address_entry);
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Condition:"));
    gtk_container_add(GTK_CONTAINER(content_area), condition_combo);
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Department:"));
    gtk_container_add(GTK_CONTAINER(content_area), department_combo);
    gtk_container_add(GTK_CONTAINER(content_area), assured_check);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
        const char *age_str = gtk_entry_get_text(GTK_ENTRY(age_entry));
        const char *medical_case = gtk_entry_get_text(GTK_ENTRY(medical_case_entry));
        const char *address = gtk_entry_get_text(GTK_ENTRY(address_entry));
        int age = atoi(age_str);

        // Get selected condition and department
        condition cond = (condition) (gtk_combo_box_get_active(GTK_COMBO_BOX(condition_combo)) + 1);
        department dept = (department) (gtk_combo_box_get_active(GTK_COMBO_BOX(department_combo)) + 1);
        bool isAssured = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(assured_check));

        // Call your data-layer function
        addPatient((char*)name, age, (char*)medical_case, (char*)address, cond, dept, isAssured);

        label = gtk_label_new("Patient added successfully!");
        gtk_container_add(GTK_CONTAINER(content_area), label);
        gtk_widget_show_all(content_area);
    }

    gtk_widget_destroy(dialog);
}
// Function to add menu bar
void addDoctors(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog, *content_area;
    GtkWidget *name_entry, *age_entry, *specialty_entry, *address_entry, *rank_entry, *department_entry;
    GtkWidget *label;
    GtkWindow *parent = NULL;
    if (widget)
        parent = GTK_WINDOW(gtk_widget_get_toplevel(widget));

    dialog = gtk_dialog_new_with_buttons(
        "Add Doctor",
        parent,
        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
        "_Add", GTK_RESPONSE_ACCEPT,
        "_Cancel", GTK_RESPONSE_REJECT,
        NULL
    );

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // Create entry fields
    name_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(name_entry), "Name");
    age_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(age_entry), "Age");
    specialty_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(specialty_entry), "Specialty");
    address_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(address_entry), "Address");
    rank_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(rank_entry), "Rank (1-6)");
    department_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(department_entry), "Department (1-4)");

    // Add entries to the dialog
    gtk_container_add(GTK_CONTAINER(content_area), gtk_label_new("Enter Doctor Details:"));
    gtk_container_add(GTK_CONTAINER(content_area), name_entry);
    gtk_container_add(GTK_CONTAINER(content_area), age_entry);
    gtk_container_add(GTK_CONTAINER(content_area), specialty_entry);
    gtk_container_add(GTK_CONTAINER(content_area), address_entry);
    gtk_container_add(GTK_CONTAINER(content_area), rank_entry);
    gtk_container_add(GTK_CONTAINER(content_area), department_entry);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        const char *name = gtk_entry_get_text(GTK_ENTRY(name_entry));
        const char *age_str = gtk_entry_get_text(GTK_ENTRY(age_entry));
        const char *specialty = gtk_entry_get_text(GTK_ENTRY(specialty_entry));
        const char *address = gtk_entry_get_text(GTK_ENTRY(address_entry));
        int age = atoi(age_str);

        const char *rank_str = gtk_entry_get_text(GTK_ENTRY(rank_entry));
        const char *department_str = gtk_entry_get_text(GTK_ENTRY(department_entry));
        int docRank = atoi(rank_str);
        int docDept = atoi(department_str);

        // Call your data-layer function
        addDoctor((char*)name, age, (char*)specialty, (char*)address, docRank, docDept);
        // Optionally, you can show a message or update the UI
        label = gtk_label_new("Doctor added successfully!");
        gtk_container_add(GTK_CONTAINER(content_area), label);
        gtk_widget_show_all(content_area);
    }

    gtk_widget_destroy(dialog);
}

void add_menu_bar(GtkWidget *vbox) {
    GtkWidget *menu_bar, *file_menu, *file_item, *exit_item;
    GtkWidget *navigate_menu, *navigate_item;
    GtkWidget *patients_item, *doctors_item, *addDoctor_item, *queue_item, *departments_item, *addPatient_item;

    menu_bar = gtk_menu_bar_new();

    // File menu
    file_menu = gtk_menu_new();
    file_item = gtk_menu_item_new_with_label("File");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_item);

    exit_item = gtk_menu_item_new_with_label("Exit");
    gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);
    g_signal_connect(exit_item, "activate", G_CALLBACK(gtk_main_quit), NULL);

    // Navigate menu
    navigate_menu = gtk_menu_new();
    navigate_item = gtk_menu_item_new_with_label("Navigate");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(navigate_item), navigate_menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), navigate_item);

    // Add navigation items
    patients_item = gtk_menu_item_new_with_label("Patients");
    doctors_item = gtk_menu_item_new_with_label("Doctors");
    addDoctor_item = gtk_menu_item_new_with_label("Add Doctor");
    addPatient_item = gtk_menu_item_new_with_label("Add Patient");
    queue_item = gtk_menu_item_new_with_label("Doctor's Queue");
    departments_item = gtk_menu_item_new_with_label("Departments");

    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), patients_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), doctors_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), addPatient_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), addDoctor_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), queue_item);
    gtk_menu_shell_append(GTK_MENU_SHELL(navigate_menu), departments_item);

    // Connect menu items to callbacks
    g_signal_connect(patients_item, "activate", G_CALLBACK(viewAllPatients), NULL);
    g_signal_connect(doctors_item, "activate", G_CALLBACK(viewAllDoctors), NULL);
    g_signal_connect(addDoctor_item, "activate", G_CALLBACK(addDoctors), NULL);
    g_signal_connect(addPatient_item, "activate", G_CALLBACK(addPatientDialog), NULL);
    g_signal_connect(queue_item, "activate", G_CALLBACK(viewDoctorQueueDialog), NULL);
    g_signal_connect(departments_item, "activate", G_CALLBACK(departmentsInfo), NULL);

    gtk_widget_set_name(menu_bar, "menu-bar");
    gtk_widget_set_margin_start(menu_bar, 10);
    gtk_widget_set_margin_end(menu_bar, 10);
    gtk_widget_set_margin_top(menu_bar, 10);
    gtk_widget_set_margin_bottom(menu_bar, 10);
    gtk_widget_set_halign(menu_bar, GTK_ALIGN_START);
    gtk_widget_set_valign(menu_bar, GTK_ALIGN_START);
    gtk_widget_set_hexpand(menu_bar, TRUE);
    gtk_widget_set_vexpand(menu_bar, FALSE);
    gtk_widget_set_size_request(menu_bar, 400, 30);

    // Add the menu bar to the vbox
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, FALSE, 0);
}

// Remove the add_buttons function and its call from main

int main(int argc, char *argv[]) {
    GtkWidget *window, *vbox;
    gtk_init(&argc, &argv);

    window = create_window();

    // Create a vertical box and add it to the window
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Add menu bar to the vbox
    add_menu_bar(vbox);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}