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
if ($_SERVER['REQUEST_METHOD'] === 'GET') {
    $query = "SELECT id, temperature, humidity, speed, fuel, gear, gps, updated_at 
              FROM tbl_car_dashboard 
              ORDER BY updated_at DESC 
              LIMIT 1";
    $result = $conn->query($query);
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        echo json_encode(["status" => "success", "data" => $row]);
    } else {
        echo json_encode(["status" => "error", "message" => "No data found"]);
    }
} else {
    echo json_encode(["status" => "error", "message" => "Invalid request method"]);
}
$conn->close();
?>
