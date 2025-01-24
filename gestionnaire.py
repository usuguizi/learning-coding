import tkinter as tk
from tkinter import ttk, messagebox
import sqlite3
from datetime import datetime, timedelta


# Database setup
def setup_database():
    conn = sqlite3.connect("tasks.db")
    cursor = conn.cursor()
    cursor.execute("""
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            description TEXT,
            category TEXT,
            due_date TEXT,
            status TEXT DEFAULT 'Pending'
        )
    """)
    conn.commit()
    conn.close()


# Add Task
def add_task():
    title = title_entry.get()
    description = description_entry.get("1.0", tk.END).strip()
    category = category_combobox.get()
    due_date = due_date_entry.get()

    if not title or not due_date:
        messagebox.showerror("Erreur", "Veuillez remplir le titre et la date d'échéance.")
        return

    try:
        datetime.strptime(due_date, "%Y-%m-%d")
    except ValueError:
        messagebox.showerror("Erreur", "La date doit être au format AAAA-MM-JJ.")
        return

    conn = sqlite3.connect("tasks.db")
    cursor = conn.cursor()
    cursor.execute("""
        INSERT INTO tasks (title, description, category, due_date)
        VALUES (?, ?, ?, ?)
    """, (title, description, category, due_date))
    conn.commit()
    conn.close()
    refresh_task_list()
    clear_form()
    messagebox.showinfo("Succès", "Tâche ajoutée avec succès !")


# Refresh Task List
def refresh_task_list():
    for item in task_tree.get_children():
        task_tree.delete(item)

    conn = sqlite3.connect("tasks.db")
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM tasks ORDER BY due_date ASC")
    tasks = cursor.fetchall()
    conn.close()

    for task in tasks:
        task_tree.insert("", "end", values=task)


# Delete Task
def delete_task():
    selected_item = task_tree.selection()
    if not selected_item:
        messagebox.showerror("Erreur", "Veuillez sélectionner une tâche à supprimer.")
        return

    task_id = task_tree.item(selected_item)["values"][0]
    conn = sqlite3.connect("tasks.db")
    cursor = conn.cursor()
    cursor.execute("DELETE FROM tasks WHERE id = ?", (task_id,))
    conn.commit()
    conn.close()
    refresh_task_list()
    messagebox.showinfo("Succès", "Tâche supprimée avec succès !")


# Clear Form
def clear_form():
    title_entry.delete(0, tk.END)
    description_entry.delete("1.0", tk.END)
    category_combobox.set("")
    due_date_entry.delete(0, tk.END)


# GUI Setup
setup_database()
root = tk.Tk()
root.title("Gestionnaire de Tâches")
root.geometry("800x600")
root.resizable(False, False)

# Title
title_label = tk.Label(root, text="Titre :", font=("Arial", 12))
title_label.grid(row=0, column=0, padx=10, pady=5, sticky="w")
title_entry = tk.Entry(root, font=("Arial", 12), width=40)
title_entry.grid(row=0, column=1, padx=10, pady=5, sticky="w")

# Description
description_label = tk.Label(root, text="Description :", font=("Arial", 12))
description_label.grid(row=1, column=0, padx=10, pady=5, sticky="nw")
description_entry = tk.Text(root, font=("Arial", 12), width=40, height=5)
description_entry.grid(row=1, column=1, padx=10, pady=5, sticky="w")

# Category
category_label = tk.Label(root, text="Catégorie :", font=("Arial", 12))
category_label.grid(row=2, column=0, padx=10, pady=5, sticky="w")
category_combobox = ttk.Combobox(root, font=("Arial", 12), values=["Personnel", "Professionnel", "Urgent"], width=38)
category_combobox.grid(row=2, column=1, padx=10, pady=5, sticky="w")

# Due Date
due_date_label = tk.Label(root, text="Échéance (AAAA-MM-JJ) :", font=("Arial", 12))
due_date_label.grid(row=3, column=0, padx=10, pady=5, sticky="w")
due_date_entry = tk.Entry(root, font=("Arial", 12), width=40)
due_date_entry.grid(row=3, column=1, padx=10, pady=5, sticky="w")

# Buttons
add_button = tk.Button(root, text="Ajouter", font=("Arial", 12), bg="#4CAF50", fg="white", command=add_task)
add_button.grid(row=4, column=1, padx=10, pady=10, sticky="w")

delete_button = tk.Button(root, text="Supprimer", font=("Arial", 12), bg="#f44336", fg="white", command=delete_task)
delete_button.grid(row=4, column=1, padx=100, pady=10, sticky="w")

clear_button = tk.Button(root, text="Effacer le formulaire", font=("Arial", 12), command=clear_form)
clear_button.grid(row=4, column=1, padx=250, pady=10, sticky="w")

# Task List
task_tree = ttk.Treeview(root, columns=("ID", "Titre", "Description", "Catégorie", "Échéance", "Statut"), show="headings")
task_tree.heading("ID", text="ID")
task_tree.heading("Titre", text="Titre")
task_tree.heading("Description", text="Description")
task_tree.heading("Catégorie", text="Catégorie")
task_tree.heading("Échéance", text="Échéance")
task_tree.heading("Statut", text="Statut")
task_tree.column("ID", width=50, anchor="center")
task_tree.grid(row=5, column=0, columnspan=3, padx=10, pady=10, sticky="nsew")

# Load Tasks
refresh_task_list()

# Start GUI
root.mainloop()
