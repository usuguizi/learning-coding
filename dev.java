import java.util.ArrayList;
import java.util.Scanner;

class Item {
    String name;
    double price;

    Item(String name, double price) {
        this.name = name;
        this.price = price;
    }
}

public class ShoppingCart {

    private ArrayList<Item> cart;

    public ShoppingCart() {
        cart = new ArrayList<>();
    }

    public void addItem(Item item) {
        cart.add(item);
    }

    public void showCart() {
        double total = 0;
        System.out.println("Items in your cart:");
        for (Item item : cart) {
            System.out.println(item.name + " - $" + item.price);
            total += item.price;
        }
        System.out.println("Total: $" + total);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        ShoppingCart shoppingCart = new ShoppingCart();

        shoppingCart.addItem(new Item("Apple", 0.99));
        shoppingCart.addItem(new Item("Banana", 1.29));
        shoppingCart.addItem(new Item("Orange", 1.49));

        shoppingCart.showCart();
    }
}
