<?php
header("Content-Type: application/json");
define("HOST", "");
define("USER", "");
define("PASSWORD", "");
define("DB", "");
function get_db_connection() {
    $connect = new mysqli(HOST, USER, PASSWORD, DB);
    if ($connect->connect_error) {
        die("Connection failed: " . $connect->connect_error);
    }
    return $connect;
}
$conn = get_db_connection();
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $temperature = $_POST['temperature'] ?? null;
    $humidity = $_POST['humidity'] ?? null;
    $speed = $_POST['speed'] ?? null;
    $fuel = $_POST['fuel'] ?? null;
    $gear = $_POST['gear'] ?? null;
    $gps = $_POST['gps'] ?? null;
    $updated_at = date('Y-m-d H:i:s');
    if (!is_null($temperature) && !is_null($humidity) && !is_null($speed) && !is_null($fuel) && !is_null($gear) && !is_null($gps)) {
        $stmt = $conn->prepare("INSERT INTO tbl_car_dashboard (temperature, humidity, speed, fuel, gear, gps, updated_at) VALUES (?, ?, ?, ?, ?, ?, ?)");
        $stmt->bind_param("dddisds", $temperature, $humidity, $speed, $fuel, $gear, $gps, $updated_at);
        if ($stmt->execute()) {
            echo json_encode(["status" => "success", "message" => "Data inserted successfully"]);
        } else {
            echo json_encode(["status" => "error", "message" => "Failed to insert data"]);
        }
        $stmt->close();
    } else {
        echo json_encode(["status" => "error", "message" => "Incomplete data"]);
    }
} elseif ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $query = "SELECT id, temperature, humidity, speed, fuel, gear, gps, updated_at FROM tbl_car_dashboard ORDER BY updated_at DESC";
    $result = $conn->query($query);
    if ($result->num_rows > 0) {
        $data = [];
        while($row = $result->fetch_assoc()) {
            $data[] = $row;
        }
        echo json_encode(["status" => "success", "data" => $data]);
    } else {
        echo json_encode(["status" => "error", "message" => "No data found"]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
$conn->close();
?>
