document.addEventListener('DOMContentLoaded', () => {
    const taskInput = document.getElementById('task-input');
    const addButton = document.getElementById('add-button');
    const taskList = document.getElementById('task-list');

    addButton.addEventListener('click', () => {
        const taskText = taskInput.value.trim();
        if (taskText) {
            // Créer l'élément de tâche
            const li = document.createElement('li');
            li.textContent = taskText;
            
            // Créer le bouton de suppression
            const deleteButton = document.createElement('button');
            deleteButton.textContent = 'Delete';
            deleteButton.classList.add('delete-button');

            // Fonction pour supprimer la tâche avec animation
            deleteButton.onclick = () => {
                li.classList.add('fade-out');
                setTimeout(() => {
                    li.remove();
                }, 500);  // Temps de l'animation avant suppression
            };

            // Ajouter le bouton de suppression à la tâche
            li.appendChild(deleteButton);

            // Ajouter la tâche à la liste
            taskList.appendChild(li);

            // Effacer l'entrée après l'ajout
            taskInput.value = '';
        }
    });

    // Facultatif : ajouter un écouteur d'événement pour ajouter la tâche en appuyant sur Entrée
    taskInput.addEventListener('keypress', (e) => {
        if (e.key === 'Enter') {
            addButton.click();
        }
    });
});
