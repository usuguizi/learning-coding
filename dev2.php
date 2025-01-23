<?php
// Lire les contacts depuis le fichier JSON
$contactsFile = 'contacts.json';
$contacts = json_decode(file_get_contents($contactsFile), true);

// Ajouter un contact
if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_POST['action'])) {
    if ($_POST['action'] == 'ajouter') {
        $nom = $_POST['nom'];
        $email = $_POST['email'];
        $telephone = $_POST['telephone'];

        // Ajouter le contact dans le fichier JSON
        $contacts[] = ['nom' => $nom, 'email' => $email, 'telephone' => $telephone];
        file_put_contents($contactsFile, json_encode($contacts, JSON_PRETTY_PRINT));
        echo "Contact ajouté avec succès ! <a href=''>Retour à la liste</a>";
    } elseif ($_POST['action'] == 'modifier' && isset($_POST['id'])) {
        $id = $_POST['id'];
        $contacts[$id]['nom'] = $_POST['nom'];
        $contacts[$id]['email'] = $_POST['email'];
        $contacts[$id]['telephone'] = $_POST['telephone'];

        // Sauvegarder le fichier JSON mis à jour
        file_put_contents($contactsFile, json_encode($contacts, JSON_PRETTY_PRINT));
        echo "Contact modifié avec succès ! <a href=''>Retour à la liste</a>";
    }
}

// Supprimer un contact
if (isset($_GET['action']) && $_GET['action'] == 'supprimer' && isset($_GET['id'])) {
    $id = $_GET['id'];

    // Supprimer le contact
    unset($contacts[$id]);

    // Réindexer les contacts
    $contacts = array_values($contacts);

    // Sauvegarder le fichier JSON mis à jour
    file_put_contents($contactsFile, json_encode($contacts, JSON_PRETTY_PRINT));
    echo "Contact supprimé avec succès ! <a href=''>Retour à la liste</a>";
}

?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Gestion des Contacts</title>
</head>
<body>
    <h1>Gestion des Contacts</h1>

    <!-- Formulaire pour ajouter un contact -->
    <h2>Ajouter un Contact</h2>
    <form method="POST">
        <input type="hidden" name="action" value="ajouter">
        Nom: <input type="text" name="nom" required><br>
        Email: <input type="email" name="email" required><br>
        Téléphone: <input type="text" name="telephone" required><br>
        <button type="submit">Ajouter</button>
    </form>

    <hr>

    <h2>Liste des Contacts</h2>

    <?php
    if (empty($contacts)) {
        echo "Aucun contact n'a été ajouté.";
    } else {
        echo "<ul>";
        foreach ($contacts as $index => $contact) {
            echo "<li>";
            echo "Nom: " . htmlspecialchars($contact['nom']) . " | Email: " . htmlspecialchars($contact['email']) . " | Téléphone: " . htmlspecialchars($contact['telephone']);
            echo " <a href='?action=supprimer&id=$index'>Supprimer</a>";
            echo " <a href='?action=modifier&id=$index'>Modifier</a>";
            echo "</li>";
        }
        echo "</ul>";
    }

    // Formulaire pour modifier un contact
    if (isset($_GET['action']) && $_GET['action'] == 'modifier' && isset($_GET['id'])) {
        $id = $_GET['id'];
        $contact = $contacts[$id];

        echo "<h2>Modifier le Contact</h2>";
        echo "<form method='POST'>
                <input type='hidden' name='action' value='modifier'>
                <input type='hidden' name='id' value='$id'>
                Nom: <input type='text' name='nom' value='" . htmlspecialchars($contact['nom']) . "' required><br>
                Email: <input type='email' name='email' value='" . htmlspecialchars($contact['email']) . "' required><br>
                Téléphone: <input type='text' name='telephone' value='" . htmlspecialchars($contact['telephone']) . "' required><br>
                <button type='submit'>Modifier</button>
              </form>";
    }
    ?>
</body>
</html>
