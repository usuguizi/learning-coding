import random
import string
import os
import logging
from datetime import datetime
from django.http import HttpResponse
from django.shortcuts import render
from django.urls import path
from django.conf import settings
from django.core.management import execute_from_command_line
from django.http import JsonResponse

# Configure Django settings for the project
settings.configure(
    DEBUG=True,
    SECRET_KEY='a_very_secret_key',
    ROOT_URLCONF=__name__,
    ALLOWED_HOSTS=['*']
)

# Set up logging
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

# Function to generate a random password
def generate_password(length=12):
    characters = string.ascii_letters + string.digits + string.punctuation
    password = ''.join(random.choice(characters) for i in range(length))
    logging.info(f"Password generated: {password}")
    return password

# Function to check password strength
def check_password_strength(password):
    if len(password) < 8:
        return "Password is too short, it should be at least 8 characters."
    if not any(char.isdigit() for char in password):
        return "Password should contain at least one digit."
    if not any(char.isupper() for char in password):
        return "Password should contain at least one uppercase letter."
    if not any(char.islower() for char in password):
        return "Password should contain at least one lowercase letter."
    if not any(char in string.punctuation for char in password):
        return "Password should contain at least one special character."
    return "Password is strong."

# User class to simulate user management
class User:
    def __init__(self, username, email):
        self.username = username
        self.email = email
        self.password = None
        self.is_authenticated = False
        logging.info(f"User created: {self.username}")

    def set_password(self, password):
        self.password = password
        logging.info(f"Password set for {self.username}")

    def authenticate(self, password):
        if self.password == password:
            self.is_authenticated = True
            logging.info(f"User {self.username} authenticated successfully.")
        else:
            logging.warning(f"Failed authentication attempt for {self.username}")

# Simulate a database of users
users_db = {}

# Function to create a new user
def create_user(username, email):
    if username in users_db:
        logging.warning(f"User {username} already exists.")
        return None
    user = User(username, email)
    users_db[username] = user
    logging.info(f"User {username} created successfully.")
    return user

# Function to simulate user login
def user_login(username, password):
    if username not in users_db:
        logging.warning(f"User {username} does not exist.")
        return "User not found."
    user = users_db[username]
    user.authenticate(password)
    if user.is_authenticated:
        return f"Welcome {username}!"
    else:
        return "Authentication failed."

# Simple Django view for homepage
def home(request):
    return HttpResponse("Welcome to the home page! Use /login to authenticate.")

# Django view for user registration
def register(request):
    if request.method == "POST":
        username = request.POST.get("username")
        email = request.POST.get("email")
        password = generate_password()  # Generate a random password
        user = create_user(username, email)
        if user:
            user.set_password(password)
            logging.info(f"Registration successful for {username}.")
            return JsonResponse({"message": f"User {username} created successfully!", "password": password})
        else:
            return JsonResponse({"message": "User creation failed."}, status=400)
    return render(request, 'register.html')

# Django view for user login
def login(request):
    if request.method == "POST":
        username = request.POST.get("username")
        password = request.POST.get("password")
        message = user_login(username, password)
        return JsonResponse({"message": message})
    return render(request, 'login.html')

# Function to log out a user (simulation)
def logout(request):
    # Simulate logging out by clearing the session or user state
    return HttpResponse("You have been logged out successfully.")

# Function to check disk usage and simulate system health
def check_system_health():
    total, used, free = os.popen('free -m').readlines()[1].split()[1:4]
    logging.info(f"Memory usage: Total={total}MB, Used={used}MB, Free={free}MB")
    disk_usage = os.popen('df -h').readlines()[1].split()[2:4]
    logging.info(f"Disk usage: Used={disk_usage[0]}, Free={disk_usage[1]}")

# Function to simulate error handling and exceptions
def simulate_error():
    try:
        raise ValueError("This is a simulated error.")
    except ValueError as e:
        logging.error(f"An error occurred: {e}")
    finally:
        logging.info("Error handling completed.")

# URL mappings for the Django app
urlpatterns = [
    path('', home),
    path('register/', register),
    path('login/', login),
    path('logout/', logout),
]

# Function to simulate a task scheduling system
def schedule_tasks():
    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    logging.info(f"Scheduled task executed at {current_time}")
    check_system_health()
    simulate_error()

# Function to generate a report (simulation)
def generate_report():
    report = "System Health Report\n"
    report += f"Generatedat: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n"
    report += "----------------------------\n"
    report += "System is running fine.\n"
    logging.info("Report generated successfully.")
    return report

# Main execution to start the Django app and simulate tasks
def main():
    # Simulate task scheduling
    schedule_tasks()

    # Simulate user creation and login
    user1 = create_user("alice", "alice@example.com")
    if user1:
        user1.set_password("SecureP@ss123")
    print(user_login("alice", "SecureP@ss123"))
    
    # Generate a report and print it
    report = generate_report()
    print(report)

    # Start Django app (this is necessary for a complete Django setup)
    execute_from_command_line(["manage.py", "runserver"])

if __name__ == "__main__":
    main()
