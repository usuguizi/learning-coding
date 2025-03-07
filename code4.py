# Projet : Gestionnaire de tâches avec priorités et échéances

import datetime

# Classe pour une tâche
class Task:
    def __init__(self, title, description, priority, due_date):
        self.title = title
        self.description = description
        self.priority = priority
        self.due_date = due_date
        self.completed = False

    def mark_complete(self):
        self.completed = True

    def __str__(self):
        status = "[X]" if self.completed else "[ ]"
        return f"{status} {self.title} (Priorité: {self.priority}, Échéance: {self.due_date})\n    Description: {self.description}"

# Classe pour gérer la liste des tâches
class TaskManager:
    def __init__(self):
        self.tasks = []

    def add_task(self, task):
        self.tasks.append(task)
        print(f"Tâcheajoutée : {task.title}")

    def remove_task(self, title):
        for task in self.tasks:
            if task.title == title:
                self.tasks.remove(task)
                print(f"Tâche supprimée : {title}")
                return
        print("Tâche nontrouvée.")

    def list_tasks(self, show_completed=False):
        print("\nListe des tâches :")
        filtered_tasks = [task for task in self.tasks if show_completed or not task.completed]
        if not filtered_tasks:
            print("Aucune tâche à afficher.")
        else:
            for task in filtered_tasks:
                print(task)

    def mark_task_complete(self, title):
        for task in self.tasks:
            if task.title == title:
                task.mark_complete()
                print(f"Tâche marquée comme terminée : {title}")
                return
        print("Tâche non trouvée.")

    def list_overdue_tasks(self):
        print("\nTâches en retard :")
        now = datetime.datetime.now().date()
        overdue_tasks = [task for task in self.tasks if not task.completed and task.due_date < now]
        if not overdue_tasks:
            print("Aucune tâche en retard.")
        else:
            for task in overdue_tasks:
                print(task)

# Fonction principale
if __name__ == "__main__":
    manager = TaskManager()

    while True:
        print("\n==================== MENU ====================")
        print("1. Ajouter une tâche")
        print("2. Supprimer une tâche")
        print("3. Lister les tâches")
        print("4. Marquer une tâche comme terminée")
        print("5. Lister les tâches en retard")
        print("6. Quitter")
        print("============================================")

        choice = input("Entrez votre choix : ")

        if choice == "1":
            title = input("Titre de la tâche : ")
            description = input("Description : ")
            priority = input("Priorité (1-5, 1 = haute) : ")
            due_date_str = input("Échéance (AAAA-MM-JJ) : ")
            try:
                due_date = datetime.datetime.strptime(due_date_str, "%Y-%m-%d").date()
                task = Task(title, description, priority, due_date)
                manager.add_task(task)
            except ValueError:
                print("Date invalide. Veuillez réessayer.")

        elif choice == "2":
            title = input("Titre de la tâche à supprimer : ")
            manager.remove_task(title)

        elif choice == "3":
            show_completed = input("Afficher les tâches terminées ? (o/n) : ").lower() == "o"
            manager.list_tasks(show_completed=show_completed)

        elif choice == "4":
            title = input("Titre de la tâche à marquer comme terminée : ")
            manager.mark_task_complete(title)

        elif choice == "5":
            manager.list_overdue_tasks()

        elif choice == "6":
            print("Merci d'avoir utilisé le gestionnaire de tâches !")
            break

        else:
            print("Choix invalide. Veuillez réessayer.")
