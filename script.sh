#!/bin/bash

# Fonction pour afficher l'utilisation du script
afficher_usage() {
    echo "Usage : $0 <dossier_source> <dossier_destination>"
    echo "Exemple : $0 /chemin/vers/source /chemin/vers/sauvegarde"
    exit 1
}

# Vérifie si les deux arguments (source et destination) sont fournis
if [ "$#" -ne 2 ]; then
    afficher_usage
fi

# Récupère les arguments
SOURCE="$1"
DESTINATION="$2"

# Vérifie si le dossier source existe
if [ ! -d "$SOURCE" ]; then
    echo "Erreur : Le dossier source '$SOURCE' n'existe pas."
    exit 1
fi

# Crée le dossier de destination s'il n'existe pas
if [ ! -d "$DESTINATION" ]; then
    echo "Le dossier destination '$DESTINATION' n'existe pas. Création en cours..."
    mkdir -p "$DESTINATION"
    echo "Dossier '$DESTINATION' créé avec succès."
fi

# Ajoute un horodatage au nom du sous-dossier de sauvegarde
TIMESTAMP=$(date +"%Y-%m-%d_%H-%M-%S")
DEST_SUBFOLDER="$DESTINATION/sauvegarde_$TIMESTAMP"
mkdir -p "$DEST_SUBFOLDER"

# Copie les fichiers du dossier source vers le sous-dossier de destination
echo "Copie des fichiers de '$SOURCE' vers '$DEST_SUBFOLDER'..."
cp -r "$SOURCE"/* "$DEST_SUBFOLDER"

# Vérifie le succès de la copie
if [ $? -eq 0 ]; then
    echo "Sauvegarde effectuée avec succès !"
    echo "Tous les fichiers ont été copiés vers '$DEST_SUBFOLDER'."
else
    echo "Il y a eu une erreur lors de la sauvegarde. Veuillez vérifier vos dossiers."
    exit 1
fi
