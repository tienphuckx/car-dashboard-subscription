#include "CarData.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QRandomGenerator>

const QString CarData::API_URL = "https://tienphuckx.ueuo.com/automotive/api-car-dashboard-qt.php";

// Constructor for CarData class
CarData::CarData(QObject *parent)
    : QObject(parent)
    , m_speedValue(0)
    , m_gearValue(0)
    , m_fuelValue(0)
    , m_tempValue(0)
    , m_humidity(0)
    , m_gps("X,Y")
    , m_timer(new QTimer(this))
{
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &CarData::onApiResponse);

    // Fetch data from API every 5 seconds
    QTimer *apiTimer = new QTimer(this);
    connect(apiTimer, &QTimer::timeout, this, &CarData::fetchDataFromAPI);
    apiTimer->start(2000); // Fetch API data every 5 seconds

    //connect each second will update time
    connect(m_timer, &QTimer::timeout, this, &CarData::updateTime);
    m_timer->start(1000); // Update every 1000 ms (1 second)

    // Set initial time
    updateTime();
}

QString CarData::currentTime() const
{
    return m_currentTime;
}

void CarData::updateTime()
{
    // Get the current time and format it as HH:mm:ss
    m_currentTime = QDateTime::currentDateTime().toString("HH:mm:ss");

    // Emit signal to notify that the time has changed
    emit timeChanged();
}

int CarData::temperatureValue() const
{
    return m_tempValue;
}

void CarData::setTemperatureValue(int value)
{
    if (m_tempValue != value) {
        m_tempValue = value;
        emit temperatureValueChanged();
    }
}

int CarData::humidity() const
{
    return m_humidity;
}

void CarData::setHumidity(int value)
{
    if (m_humidity != value) {
        m_humidity = value;
        emit humidityChanged();
    }
}

QString CarData::gps() const
{
    return m_gps;
}

void CarData::setGps(QString value)
{
    if (m_gps != value) {
        m_gps = value;
        emit gpsChanged();
    }
}

// Speed-related methods
int CarData::speedValue() const
{
    return m_speedValue;
}

void CarData::setSpeedValue(int value)
{
    if (m_speedValue != value) {
        m_speedValue = value;
        emit speedValueChanged(m_speedValue);
    }
}

// Gear-related methods
int CarData::gearValue() const
{
    return m_gearValue;
}

void CarData::setGearValue(int value)
{
    if (m_gearValue != value) {
        m_gearValue = value;
        emit gearValueChanged();
    }
}

// Fuel-related methods
int CarData::fuelValue() const
{
    return m_fuelValue;
}

void CarData::setFuelValue(int value)
{
    if (m_fuelValue != value) {
        m_fuelValue = value;
        emit fuelValueChanged();
    }
}

void CarData::fetchDataFromAPI()
{
    QUrl url(API_URL);
    QNetworkRequest request(url);
    m_networkManager->get(request);
}

void CarData::onApiResponse(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        // Access the "data" object from the JSON response
        QJsonObject dataObject = jsonObject["data"].toObject();

        // Now extract the values from the "data" object
        float apiSpeed = dataObject["speed"].toString().toFloat();
        int apiGear = dataObject["gear"].toString().toInt();
        int apiFuel = dataObject["fuel"].toString().toInt();
        float apiTemperature = dataObject["temperature"].toString().toFloat();
        float apiHumidity = dataObject["humidity"].toString().toInt();
        QString apiGps = dataObject["gps"].toString();
        QString timeUpdate = dataObject["updated_at"].toString();

        // Update values from API response
        setSpeedValue(static_cast<int>(apiSpeed)); // Assuming setSpeedValue expects an int
        setGearValue(apiGear);
        setFuelValue(apiFuel);
        setHumidity(apiHumidity);
        setGps(apiGps);

        setTemperatureValue(
            static_cast<int>(apiTemperature)); // Assuming setTemperatureValue expects an int

        qDebug() << "fetchDataFromAPI: Speed:" << apiSpeed << "Gear:" << apiGear
                 << "Fuel:" << apiFuel << "Humidity:" << apiGear << "GPS:" << apiFuel
                 << "Temp:" << apiTemperature << "Temp:" << apiTemperature << "Time:" << timeUpdate;
    } else {
        qDebug() << "API request failed: " << reply->errorString();
    }
    reply->deleteLater();
}
