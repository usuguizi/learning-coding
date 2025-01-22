<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $num1 = $_POST['num1'];
    $num2 = $_POST['num2'];
    $operation = $_POST['operation'];
    
    if ($operation == 'add') {
        $result = $num1 + $num2;
    } elseif ($operation == 'subtract') {
        $result = $num1 - $num2;
    } elseif ($operation == 'multiply') {
        $result = $num1 * $num2;
    } elseif ($operation == 'divide') {
        $result = $num1 / $num2;
    }
} else {
    $result = null;
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Simple Calculator</title>
</head>
<body>
    <h1>Simple PHP Calculator</h1>
    <form method="POST">
        <input type="number" name="num1" required>
        <input type="number" name="num2" required>
        <select name="operation" required>
            <option value="add">Add</option>
            <option value="subtract">Subtract</option>
            <option value="multiply">Multiply</option>
            <option value="divide">Divide</option>
        </select>
        <button type="submit">Calculate</button>
    </form>

    <?php if ($result !== null): ?>
        <h2>Result: <?= $result ?></h2>
    <?php endif; ?>
</body>
</html>
