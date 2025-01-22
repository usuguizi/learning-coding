#!/bin/bash

# Fonction pour afficher un message d'erreur et quitter le script
error_exit() {
    echo "$1" 1>&2
    exit 1
}

# Fonction pour envoyer une notification par email (exigera une configuration de serveur mail comme Sendmail ou SSMTP)
send_email_notification() {
    local subject="$1"
    local body="$2"
    local to_email="$3"
    echo -e "Subject:${subject}\n\n${body}" | sendmail "$to_email" || echo "Erreur: L'envoi de l'email a échoué." 1>&2
}

# Fonction pour vérifier si un répertoire existe
check_directory_exists() {
    if [ ! -d "$1" ]; then
        error_exit "Erreur: Le répertoire '$1' n'existe pas."
    fi
}

# Fonction pour vérifier si un fichier existe
check_file_exists() {
    if [ ! -f "$1" ]; then
        error_exit "Erreur: Le fichier '$1' n'existe pas."
    fi
}

# Fonction pour vérifier les permissions d'écriture sur un répertoire
check_write_permission() {
    if [ ! -w "$1" ]; then
        error_exit "Erreur: Permission d'écriture refusée sur '$1'."
    fi
}

# Fonction pour compresser un répertoire en archive tar.gz
compress_directory() {
    local source_dir="$1"
    local backup_file="$2"
    echo "Compression du répertoire '$source_dir' en archive..."
    tar -czf "$backup_file" "$source_dir" 2>> "$LOG_FILE" || error_exit "Erreur lors de la compression du répertoire."
    echo "Compression terminée : '$backup_file'." | tee -a "$LOG_FILE"
}

# Fonction pour nettoyer les anciennes sauvegardes (plus anciennes que 7 jours)
clean_old_backups() {
    local backup_dir="$1"
    echo "Suppression des sauvegardes plus anciennes que 7 jours..."
    find "$backup_dir" -name 'backup_*.tar.gz' -type f -mtime +7 -exec rm -f {} \; 2>> "$LOG_FILE" || error_exit "Erreur lors de la suppression des anciennes sauvegardes."
    echo "Nettoyage terminé." | tee -a "$LOG_FILE"
}

# Fonction pour sauvegarder un fichier de configuration
backup_configuration() {
    local source_file="$1"
    local backup_dir="$2"
    local backup_file="$backup_dir/$(basename "$source_file")_$(date +'%Y%m%d').bak"
    echo "Sauvegarde du fichier de configuration '$source_file'..."
    cp "$source_file" "$backup_file" || error_exit "Erreur lors de la sauvegarde du fichier '$source_file'."
    echo "Fichier de configuration sauvegardé sous '$backup_file'." | tee -a "$LOG_FILE"
}

# Fonction pour enregistrer les logs détaillés dans un fichier
log_message() {
    local message="$1"
    echo "$(date +'%Y-%m-%d %H:%M:%S') - $message" | tee -a "$LOG_FILE"
}

# Fonction pour afficher l'usage du script
usage() {
    echo "Usage: $0 <source_directory> <backup_directory> <log_file> <email>"
    echo "  <source_directory>  : Le répertoire à sauvegarder."
    echo "  <backup_directory>  : Le répertoire où la sauvegarde sera stockée."
    echo "  <log_file>          : Le fichier journal pour enregistrer l'activité."
    echo "  <email>             : L'email où les notifications seront envoyées."
    exit 1
}

# Vérification des arguments
if [ $# -ne 4 ]; then
    usage
fi

SOURCE_DIR="$1"               # Répertoire source à sauvegarder
BACKUP_DIR="$2"               # Répertoire où la sauvegarde sera stockée
LOG_FILE="$3"                 # Fichier journal pour enregistrer les informations de sauvegarde
TO_EMAIL="$4"                 # Email pour les notifications

# Vérification des entrées
check_directory_exists "$SOURCE_DIR"
check_write_permission "$BACKUP_DIR"
check_file_exists "$LOG_FILE"

# Nom du fichier de sauvegarde
DATE=$(date +'%Y-%m-%d_%H-%M-%S')
BACKUP_FILE="$BACKUP_DIR/backup_$DATE.tar.gz"

# Début de la sauvegarde
log_message "Démarrage de la sauvegarde de '$SOURCE_DIR' vers '$BACKUP_FILE'..."

# Compression du répertoire source
compress_directory "$SOURCE_DIR" "$BACKUP_FILE"

# Sauvegarde d'un fichier de configuration (exemple avec /etc/hostname)
CONFIG_FILE="/etc/hostname"
backup_configuration "$CONFIG_FILE" "$BACKUP_DIR"

# Nettoyage des anciennes sauvegardes
clean_old_backups "$BACKUP_DIR"

# Envoi d'une notification par email en cas de succès
send_email_notification "Sauvegarde réussie" \
"La sauvegarde de '$SOURCE_DIR' a été effectuée avec succès et stockée dans '$BACKUP_FILE'.\n\nLa sauvegarde a également nettoyé les anciennes sauvegardes." \
"$TO_EMAIL"

# Fin de la sauvegarde
log_message "Sauvegarde terminée avec succès."

# Récapitulation dans le terminal
echo "Sauvegarde réussie !"

exit 0
