#ifndef CARDATA_H
#define CARDATA_H

#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>

class CarData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speedValue READ speedValue WRITE setSpeedValue NOTIFY speedValueChanged)
    Q_PROPERTY(int gearValue READ gearValue WRITE setGearValue NOTIFY gearValueChanged)
    Q_PROPERTY(int fuelValue READ fuelValue WRITE setFuelValue NOTIFY fuelValueChanged)
    Q_PROPERTY(int temperatureValue READ temperatureValue WRITE setTemperatureValue NOTIFY
                   temperatureValueChanged FINAL)
    Q_PROPERTY(int humidity READ humidity WRITE setHumidity NOTIFY humidityChanged FINAL)
    Q_PROPERTY(QString gps READ gps WRITE setGps NOTIFY gpsChanged FINAL)
    Q_PROPERTY(QString currentTime READ currentTime NOTIFY timeChanged)

public:
    explicit CarData(QObject *parent = nullptr);

    QString currentTime() const;

    // Speed
    int speedValue() const;
    void setSpeedValue(int value);

    // Gear
    int gearValue() const;
    void setGearValue(int value);

    // Fuel
    int fuelValue() const;
    void setFuelValue(int value);

    // temperature
    int temperatureValue() const;
    void setTemperatureValue(int value);

    //humidity
    int humidity() const;
    void setHumidity(int value);

    //gps
    QString gps() const;
    void setGps(QString value);

signals:
    void speedValueChanged(int newValue);
    void gearValueChanged();
    void fuelValueChanged();
    void temperatureValueChanged();
    void humidityChanged();
    void gpsChanged();
    void timeChanged();

public slots:
    void fetchDataFromAPI();

private slots:
    void onApiResponse(QNetworkReply *reply);
    void updateTime();

private:
    int m_speedValue;
    int m_gearValue;
    int m_fuelValue;
    int m_tempValue;
    int m_humidity;
    QString m_gps;

    QNetworkAccessManager *m_networkManager;
    static const QString API_URL;

    //for time change
    QString m_currentTime;
    QTimer *m_timer;
};

#endif // CARDATA_H
