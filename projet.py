import requests
import tkinter as tk
from tkinter import messagebox

def check_email_breach(email):
    api_url = f"https://haveibeenpwned.com/api/v3/breachedaccount/{email}"
    headers = {
        "hibp-api-key": "VOTRE_CLE_API",  # Remplacez par votre clé API
        "User-Agent": "EmailBreachChecker"
    }
    
    try:
        response = requests.get(api_url, headers=headers)
        
        if response.status_code == 200:
            breaches = response.json()
            result_text = f"L'e-mail {email} a été trouvé dans les fuites suivantes:\n"
            for breach in breaches:
                result_text += f"- {breach['Name']} ({breach['BreachDate']})\n"
            messagebox.showinfo("Résultat", result_text)
        elif response.status_code == 404:
            messagebox.showinfo("Résultat", f"Aucune fuite trouvée pour {email}.")
        else:
            messagebox.showerror("Erreur", f"Erreur: {response.status_code}, {response.text}")
    except requests.RequestException as e:
        messagebox.showerror("Erreur", f"Erreur de connexion: {e}")

def on_check_button_click():
    email = email_entry.get()
    if email:
        check_email_breach(email)
    else:
        messagebox.showwarning("Avertissement", "Veuillez entrer une adresse e-mail.")

# Interface graphique avec Tkinter
root = tk.Tk()
root.title("Vérificateur de fuite d'e-mail")
root.geometry("400x200")

tk.Label(root, text="Entrez l'adresse e-mail à vérifier:").pack(pady=5)
email_entry = tk.Entry(root, width=40)
email_entry.pack(pady=5)

tk.Button(root, text="Vérifier", command=on_check_button_click).pack(pady=10)

root.mainloop()
