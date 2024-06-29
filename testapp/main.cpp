#include "Settings.h"
const std::string filename = "config.yml";
void test_1_general_case();
void test_2_node_not_present();
void test_3();
void test_4();
void test_5();
void test_6();
void test_7();
void test_8();
void test_9();
void test_10();
void test_11();
void test_12();

int main() {
    test_1_general_case();
    test_2_node_not_present();
    test_3();
    test_4();
    test_5();
    test_6();
    test_7();
    test_8();
    test_9();
    test_10();
    test_11();
    //test_12();
    return 0;
}

void test_1_general_case()
{
    std::cout << std::endl << std::endl;
    std::cout << "=============================================================" << std::endl;
    std::cout << "test_1_general_case" << std::endl;
    std::cout << "=============================================================" << std::endl;

    Settings settings(filename);

    settings.setValue("/application/version", "1.0.0");
    settings.setValue("/application/update/checkInterval", "7");
    settings.setValue("/database/connection/timeout", "30");
    settings.setValue("/database/connection/retry/attempts", "5");
    settings.setValue("/features/enableExperimental/featureX", "true");
    settings.setValue("/features/enableExperimental/featureY", "false");
    settings.setValue("/network/proxy/http/enabled", "true");
    settings.setValue("/network/proxy/http/port", "8080");
    settings.setValue("/network/proxy/https/enabled", "false");
    settings.setValue("/network/proxy/https/port", "443");
    settings.setValue("/preferences/appearance/theme", "dark");
    settings.setValue("/preferences/appearance/font/size", "14");
    settings.setValue("/preferences/appearance/font/type", "Arial");
    settings.setValue("/user/profile/displayName", "JohnDoe");
    settings.setValue("/user/profile/credentials/password/lastChanged", "2023-06-29");
    settings.setValue("/user/notifications/email/enabled", "true");
    settings.setValue("/user/notifications/email/frequency", "daily");
    settings.setValue("/user/notifications/sms/enabled", "false");
    settings.setValue("/user/settings/privacy/locationTracking", "false");
    settings.setValue("/user/settings/privacy/dataSharing/thirdParties", "false");
    settings.setValue("/logging/level", "info");
    settings.setValue("/logging/output/file/path", "/var/log/app.log");
    settings.setValue("/logging/output/console/enabled", "true");
    settings.setValue("/security/encryption/enabled", "true");
    settings.setValue("/security/encryption/key", "mysecretkey");
    settings.setValue("/backup/schedule/daily/enabled", "true");
    settings.setValue("/backup/schedule/daily/time", "02:00");
    settings.setValue("/backup/schedule/weekly/enabled", "false");
    settings.setValue("/backup/schedule/weekly/day", "Sunday");

    std::string appVersion = settings.value("/application/version");
    std::string updateCheckInterval = settings.value("/application/update/checkInterval");
    std::string dbConnectionTimeout = settings.value("/database/connection/timeout");
    std::string dbConnectionRetryAttempts = settings.value("/database/connection/retry/attempts");
    std::string featureXEnabled = settings.value("/features/enableExperimental/featureX");
    std::string featureYEnabled = settings.value("/features/enableExperimental/featureY");
    std::string httpProxyEnabled = settings.value("/network/proxy/http/enabled");
    std::string httpProxyPort = settings.value("/network/proxy/http/port");
    std::string httpsProxyEnabled = settings.value("/network/proxy/https/enabled");
    std::string httpsProxyPort = settings.value("/network/proxy/https/port");
    std::string appTheme = settings.value("/preferences/appearance/theme");
    std::string fontSize = settings.value("/preferences/appearance/font/size");
    std::string fontType = settings.value("/preferences/appearance/font/type");
    std::string displayName = settings.value("/user/profile/displayName");
    std::string passwordLastChanged = settings.value("/user/profile/credentials/password/lastChanged");
    std::string emailNotificationsEnabled = settings.value("/user/notifications/email/enabled");
    std::string emailNotificationsFrequency = settings.value("/user/notifications/email/frequency");
    std::string smsNotificationsEnabled = settings.value("/user/notifications/sms/enabled");
    std::string locationTrackingEnabled = settings.value("/user/settings/privacy/locationTracking");
    std::string dataSharingWithThirdParties = settings.value("/user/settings/privacy/dataSharing/thirdParties");
    std::string logLevel = settings.value("/logging/level");
    std::string logFilePath = settings.value("/logging/output/file/path");
    std::string consoleLoggingEnabled = settings.value("/logging/output/console/enabled");
    std::string encryptionEnabled = settings.value("/security/encryption/enabled");
    std::string encryptionKey = settings.value("/security/encryption/key");
    std::string dailyBackupEnabled = settings.value("/backup/schedule/daily/enabled");
    std::string dailyBackupTime = settings.value("/backup/schedule/daily/time");
    std::string weeklyBackupEnabled = settings.value("/backup/schedule/weekly/enabled");
    std::string weeklyBackupDay = settings.value("/backup/schedule/weekly/day");

    std::cout << "/application/version: " << appVersion << std::endl;
    std::cout << "/application/update/checkInterval: " << updateCheckInterval << std::endl;
    std::cout << "/database/connection/timeout: " << dbConnectionTimeout << std::endl;
    std::cout << "/database/connection/retry/attempts: " << dbConnectionRetryAttempts << std::endl;
    std::cout << "/features/enableExperimental/featureX: " << featureXEnabled << std::endl;
    std::cout << "/features/enableExperimental/featureY: " << featureYEnabled << std::endl;
    std::cout << "/network/proxy/http/enabled: " << httpProxyEnabled << std::endl;
    std::cout << "/network/proxy/http/port: " << httpProxyPort << std::endl;
    std::cout << "/network/proxy/https/enabled: " << httpsProxyEnabled << std::endl;
    std::cout << "/network/proxy/https/port: " << httpsProxyPort << std::endl;
    std::cout << "/preferences/appearance/theme: " << appTheme << std::endl;
    std::cout << "/preferences/appearance/font/size: " << fontSize << std::endl;
    std::cout << "/preferences/appearance/font/type: " << fontType << std::endl;
    std::cout << "/user/profile/displayName: " << displayName << std::endl;
    std::cout << "/user/profile/credentials/password/lastChanged: " << passwordLastChanged << std::endl;
    std::cout << "/user/notifications/email/enabled: " << emailNotificationsEnabled << std::endl;
    std::cout << "/user/notifications/email/frequency: " << emailNotificationsFrequency << std::endl;
    std::cout << "/user/notifications/sms/enabled: " << smsNotificationsEnabled << std::endl;
    std::cout << "/user/settings/privacy/locationTracking: " << locationTrackingEnabled << std::endl;
    std::cout << "/user/settings/privacy/dataSharing/thirdParties: " << dataSharingWithThirdParties << std::endl;
    std::cout << "/logging/level: " << logLevel << std::endl;
    std::cout << "/logging/output/file/path: " << logFilePath << std::endl;
    std::cout << "/logging/output/console/enabled: " << consoleLoggingEnabled << std::endl;
    std::cout << "/security/encryption/enabled: " << encryptionEnabled << std::endl;
    std::cout << "/security/encryption/key: " << encryptionKey << std::endl;
    std::cout << "/backup/schedule/daily/enabled: " << dailyBackupEnabled << std::endl;
    std::cout << "/backup/schedule/daily/time: " << dailyBackupTime << std::endl;
    std::cout << "/backup/schedule/weekly/enabled: " << weeklyBackupEnabled << std::endl;
    std::cout << "/backup/schedule/weekly/day: " << weeklyBackupDay << std::endl;

    settings.save();
    // settings.delete_file();
}

void test_2_node_not_present()
{
    std::cout << std::endl << std::endl;
    std::cout << "=============================================================" << std::endl;
    std::cout << "test_2_node_not_present " << std::endl;
    std::cout << "=============================================================" << std::endl;

    Settings settings(filename);
    std::string iamnotpresent = settings.value("/application/iamnotpresent");
    std::cout << "application/iamnotpresent: " << iamnotpresent << std::endl;

    settings.delete_file();
}


void test_3()
{
    Settings settings(filename);
    std::vector<std::pair<std::string, std::string>> keyValues = {
        {"wrapMargin2", "200"},
        {"wrapMargin3", "300"},
        {"wrapMargin4", "400"},
        {"wrapMargin5", "500"},
    };

    settings.setValues("/editor", keyValues);
    settings.save();
    settings.delete_file();
}

void test_4()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test Multiple Slash" << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("////aaaa///bbbb", "cccc");
    settings.save();
    settings.delete_file();
}

void test_5()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("////aaaa", "cccc");
    settings.save();
    settings.delete_file();
}

void test_6()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("////bbbb///", "cccc");
    settings.save();
    settings.delete_file();
}

void test_7()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("a\\b\\c", "1234");
    settings.save();
    settings.delete_file();
}

void test_8()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("eeeeeee/ffffff/gggggg", " ");
    settings.save();
    settings.delete_file();
}

void test_9()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("eeeeeee/ffffff/gggggg/a/b/c/d/e/f/g/h////", "good");
    settings.save();
    settings.delete_file();
}

void test_10()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "god");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "good");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "goood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "gooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "goooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "goooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/h////", "gooooood");
    settings.save();
    settings.delete_file();
}

void test_11()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "goooooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "gooooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "goooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "gooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "goooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "gooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "goood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "good");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i/i///", "god");
    settings.save();
    settings.delete_file();
}

void test_12()
{
    std::cout << "=============================================================" << std::endl;
    std::cout << "Test " << std::endl;
    std::cout << "=============================================================" << std::endl;
    Settings settings(filename);
    std::string ret = settings.value("e/f/g/a/b/c/d", "goooooooood");
    std::cout << "ret: " << ret << std::endl;
}