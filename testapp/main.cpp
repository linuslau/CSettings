#include "Settings.h"
const std::string filename = "config.yml";

#define PRINT_FUNCTION_NAME() do { \
    std::cout << std::endl << std::endl; \
    std::cout << "=============================================================" << std::endl; \
    std::cout << __FUNCTION__ << std::endl; \
    std::cout << "=============================================================" << std::endl; \
} while (0)

void test_1_general_case();
void test_2_node_not_present();
void test_2_1_node_not_present_ret_default();
void test_3_batch_set_values();
void test_3_1_batch_set_values_random_nodes();
void test_3_2_batch_set_values_random_nodes_multiple_slashes();
void test_4_multiple_slashes();
void test_5_start_w_mutiple_slashes();
void test_6_end_w_mutiple_slashes();
void test_7_back_slash();
void test_8_empty_value();
void test_9_node_max_depths();
void test_10_value_overwrite_len_increase();
void test_11_value_overwrite_len_decrease();
void test_12_1_conflict_map_over_key();
void test_12_2_conflict_key_over_map();
void test_13_parse_yaml_file();
void test_14_file_path_present();
void test_14_1_file_path_not_present();
void test_14_2_file_path_not_present_check();
void test_15_filename_empty();

int main() {
    PRINT_FUNCTION_NAME();
    test_1_general_case();
    test_2_node_not_present();
    test_2_1_node_not_present_ret_default();
    test_3_batch_set_values();
    test_3_1_batch_set_values_random_nodes();
    test_3_2_batch_set_values_random_nodes_multiple_slashes();
    test_4_multiple_slashes();
    test_5_start_w_mutiple_slashes();
    test_6_end_w_mutiple_slashes();
    test_7_back_slash();
    test_8_empty_value();
    test_9_node_max_depths();
    test_10_value_overwrite_len_increase();
    test_11_value_overwrite_len_decrease();
    test_12_1_conflict_map_over_key();
    test_12_2_conflict_key_over_map();
    test_13_parse_yaml_file();
    test_14_file_path_present();
    //test_14_1_file_path_not_present();
    test_14_2_file_path_not_present_check();
    test_15_filename_empty();
    return 0;
}

void test_1_general_case()
{
    PRINT_FUNCTION_NAME();

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
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    std::string iamnotpresent = settings.value("/application/iamnotpresent");
    std::cout << "application/iamnotpresent: " << iamnotpresent << std::endl;

    settings.delete_file();
}

void test_2_1_node_not_present_ret_default()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    std::string iamnotpresent = settings.value("/application/iamnotpresent", "myDefaultValue");
    std::cout << "application/iamnotpresent: " << iamnotpresent << std::endl;

    settings.delete_file();
}

void test_3_batch_set_values()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    std::vector<std::pair<std::string, std::string>> keyValues = {
        {"maxConnections", "100"},
        {"timeout", "30"},
        {"retryAttempts", "3"},
        {"enableCache", "true"},
    };

    settings.setValues("/network/config", keyValues);
    settings.save();
    settings.delete_file();
}


void test_3_1_batch_set_values_random_nodes()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    std::vector<std::pair<std::string, std::string>> keyValues = {
        {"1/2/3/maxConnections", "100"},
        {"1/timeout", "30"},
        {"1/2/retryAttempts", "3"},
        {"enableCache", "true"},
    };

    settings.setValues("/network/config", keyValues);
    settings.save();
    settings.delete_file();
}

void test_3_2_batch_set_values_random_nodes_multiple_slashes()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);

    // Example key-values with random paths and multiple slashes
    std::vector<std::pair<std::string, std::string>> keyValues = {
        {"////maxConnections/////", "100"},
        {"//timeout///", "30"},
        {"retryAttempts///", "3"},
        {"////enableCache", "true"},
        {"///cacheSize///", "512"},
        {"//proxyEnabled///", "false"},
        {"//proxyPort", "8080"},
        {"//compression", "gzip"},
        {"////encryption///", "AES256"},
        {"//loadBalancing/////", "round-robin"}
    };

    settings.setValues("/network/config", keyValues);
    settings.save();
    settings.delete_file();
}


void test_4_multiple_slashes()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("////network///config///////////proxyPort", "8080");
    settings.save();
    settings.delete_file();
}

void test_5_start_w_mutiple_slashes()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("////timeout", "8888");
    settings.save();
    settings.delete_file();
}

void test_6_end_w_mutiple_slashes()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("////preferences///", "dark");
    settings.save();
    settings.delete_file();
}

void test_7_back_slash()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("\\schedule\\time", "12:34");
    settings.save();
    settings.delete_file();
}

void test_8_empty_value()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("features/enableExperimental/featureX", " ");
    settings.save();
    settings.delete_file();
}

void test_9_node_max_depths()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t", "cool");
    settings.save();
    settings.delete_file();
}

void test_10_value_overwrite_len_increase()
{
    PRINT_FUNCTION_NAME();

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

void test_11_value_overwrite_len_decrease()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "goooooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "gooooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "goooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "gooooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "goooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "gooood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "goood");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "good");
    settings.setValue("e/f/g/a/b/c/d/e/f/g/i////", "god");
    settings.save();
    settings.delete_file();
}

void test_12_1_conflict_map_over_key()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("/database/connection/retry", "5");
    settings.setValue("/database/connection/retry/attempts", "5");
    settings.save();

    settings.setValue("/database/connection/retry", "5");
    settings.setValue("/database/connection/retry/attempts", "5", false);
    settings.save();
    settings.delete_file();

}

void test_12_2_conflict_key_over_map()
{
    PRINT_FUNCTION_NAME();

    Settings settings(filename);
    settings.setValue("/database/connection/retry/attempts", "5");
    settings.setValue("/database/connection/retry", "5");
    settings.save();

    settings.setValue("/database/connection/retry/attempts", "5");
    settings.setValue("/database/connection/retry", "5", false);
    settings.save();

    settings.delete_file();
}

void test_13_parse_yaml_file()
{
    PRINT_FUNCTION_NAME();
    test_1_general_case();
    Settings settings(filename);
    settings.parseYamlFile();
    settings.delete_file();
}

void test_14_file_path_present()
{
    PRINT_FUNCTION_NAME();
    std::string file_path = "c:/Users/kz/Documents/config.yml";

    Settings settings(file_path);

    settings.setValue("/application/version", "1.0.0");
    settings.setValue("/application/update/checkInterval", "7");
    settings.setValue("/database/connection/timeout", "30");
    settings.setValue("/database/connection/retry/attempts", "5");
    settings.setValue("/features/enableExperimental/featureX", "true");
    settings.setValue("/features/enableExperimental/featureY", "false");

    std::string appVersion = settings.value("/application/version");
    std::string updateCheckInterval = settings.value("/application/update/checkInterval");
    std::string dbConnectionTimeout = settings.value("/database/connection/timeout");
    std::string dbConnectionRetryAttempts = settings.value("/database/connection/retry/attempts");
    std::string featureXEnabled = settings.value("/features/enableExperimental/featureX");
    std::string featureYEnabled = settings.value("/features/enableExperimental/featureY");

    std::cout << "/application/version: " << appVersion << std::endl;
    std::cout << "/application/update/checkInterval: " << updateCheckInterval << std::endl;
    std::cout << "/database/connection/timeout: " << dbConnectionTimeout << std::endl;
    std::cout << "/database/connection/retry/attempts: " << dbConnectionRetryAttempts << std::endl;
    std::cout << "/features/enableExperimental/featureX: " << featureXEnabled << std::endl;
    std::cout << "/features/enableExperimental/featureY: " << featureYEnabled << std::endl;

    settings.save();
}

void test_14_1_file_path_not_present()
{
    PRINT_FUNCTION_NAME();
    std::string file_path = "c:/Users/WhoAmI/Documents/config.yml";
    Settings settings(file_path);
    try {
        settings.setValue("/application/version", "1.0.0");
    }
    catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            // return;
    }
    std::cout << "Do something else" << std::endl;
    return;
}

void test_14_2_file_path_not_present_check()
{
    PRINT_FUNCTION_NAME();
    std::string file_path = "c:/Users/WhoAmI/Documents/config.yml";
    Settings settings(file_path);

    if (!settings.isValid()) {
        std::cerr << "Failed to initialize settings. Error: \n" << settings.getLastError() << std::endl;
        return;
    }
    else {
        std::cout << "Do something else" << std::endl;
        settings.setValue("/application/version", "1.0.0");
    }
    return;
}

void test_15_filename_empty()
{
    PRINT_FUNCTION_NAME();

    Settings settings;

    settings.setValue("/application/version", "1.0.0");
    settings.setValue("/application/update/checkInterval", "7");
    settings.setValue("/database/connection/timeout", "30");
    settings.setValue("/database/connection/retry/attempts", "5");
    settings.setValue("/features/enableExperimental/featureX", "true");
    settings.setValue("/features/enableExperimental/featureY", "false");

    std::string appVersion = settings.value("/application/version");
    std::string updateCheckInterval = settings.value("/application/update/checkInterval");
    std::string dbConnectionTimeout = settings.value("/database/connection/timeout");
    std::string dbConnectionRetryAttempts = settings.value("/database/connection/retry/attempts");
    std::string featureXEnabled = settings.value("/features/enableExperimental/featureX");
    std::string featureYEnabled = settings.value("/features/enableExperimental/featureY");

    std::cout << "/application/version: " << appVersion << std::endl;
    std::cout << "/application/update/checkInterval: " << updateCheckInterval << std::endl;
    std::cout << "/database/connection/timeout: " << dbConnectionTimeout << std::endl;
    std::cout << "/database/connection/retry/attempts: " << dbConnectionRetryAttempts << std::endl;
    std::cout << "/features/enableExperimental/featureX: " << featureXEnabled << std::endl;
    std::cout << "/features/enableExperimental/featureY: " << featureYEnabled << std::endl;

    settings.save();
}
