import os

# Classe représentant une tâche
class Task:
    def __init__(self, title, description):
        self.title = title
        self.description = description
        self.completed = False
    
    def __str__(self):
        status = "Done" if self.completed else "Pending"
        return f"{self.title} - {status}\nDescription: {self.description}"

    def mark_completed(self):
        self.completed = True

# Classe représentant le gestionnaire de tâches
class ToDoManager:
    def __init__(self):
        self.tasks = []

    def add_task(self, title, description):
        task = Task(title, description)
        self.tasks.append(task)
        print(f"Task '{title}' added successfully!\n")

    def remove_task(self, title):
        task_to_remove = None
        for task in self.tasks:
            if task.title == title:
                task_to_remove = task
                break
        if task_to_remove:
            self.tasks.remove(task_to_remove)
            print(f"Task '{title}' removed successfully!\n")
        else:
            print(f"Task '{title}' not found!\n")

    def mark_task_completed(self, title):
        task_to_mark = None
        for task in self.tasks:
            if task.title == title:
                task_to_mark = task
                break
        if task_to_mark:
            task_to_mark.mark_completed()
            print(f"Task '{title}' marked as completed!\n")
        else:
            print(f"Task '{title}' not found!\n")

    def display_tasks(self):
        if not self.tasks:
            print("No tasks available.\n")
        else:
            print("Tasks List:")
            for task in self.tasks:
                print(task)
            print()

    def save_to_file(self):
        with open("tasks.txt", "w") as file:
            for task in self.tasks:
                status = "completed" if task.completed else "pending"
                file.write(f"{task.title} - {status}\n{task.description}\n\n")
        print("Tasks saved to 'tasks.txt'.\n")

    def load_from_file(self):
        if not os.path.exists("tasks.txt"):
            print("No saved tasks found.\n")
            return
        with open("tasks.txt", "r") as file:
            lines = file.readlines()
            tasks = []
            i = 0
            while i < len(lines):
                title, status = lines[i].strip().split(" - ")
                description = lines[i + 1].strip()
                task = Task(title, description)
                task.completed = True if status == "completed" else False
                tasks.append(task)
                i += 3
            self.tasks = tasks
        print("Tasks loaded from 'tasks.txt'.\n")

# Fonction principale
def main():
    manager = ToDoManager()
    manager.load_from_file()

    while True:
        print("To-Do List Menu:")
        print("1. Add Task")
        print("2. Remove Task")
        print("3. Mark Task Completed")
        print("4. Display Tasks")
        print("5. Save Tasks to File")
        print("6. Exit")
        choice = input("Choose an option: ")

        if choice == "1":
            title = input("Enter task title: ")
            description = input("Enter task description: ")
            manager.add_task(title, description)

        elif choice == "2":
            title = input("Enter the task title to remove: ")
            manager.remove_task(title)

        elif choice == "3":
            title = input("Enter the task title to mark as completed: ")
            manager.mark_task_completed(title)

        elif choice == "4":
            manager.display_tasks()

        elif choice == "5":
            manager.save_to_file()

        elif choice == "6":
            print("Goodbye!")
            manager.save_to_file()
            break

        else:
            print("Invalid option, please try again.\n")

# Exécution du programme
if __name__ == "__main__":
    main()
