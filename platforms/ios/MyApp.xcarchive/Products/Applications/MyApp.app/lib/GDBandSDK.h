//
//  GDBandSDK.h
//  GDBandSDK
//
//  Created by darren on 15/10/25.
//  Copyright © 2015年 gieseckedevrient. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#define GDCentralManagerStateChangedNotification        @"GDCentralManagerStateChangedNotification"

#define LC_MAX 256
/* ADPU-Header command structure ---------------------------------------------*/
typedef struct
{
    uint8_t CLA;  /* Command class */
    uint8_t INS;  /* Operation code */
    uint8_t P1;   /* Selection Mode */
    uint8_t P2;   /* Selection Option */
} SC_Header;

/* ADPU-Body command structure -----------------------------------------------*/
typedef struct
{
    uint8_t LC;           /* Data field length */
    uint8_t Data[LC_MAX];  /* Command parameters */
    uint8_t LE;           /* Expected length of data to be returned */
} SC_Body;

/* ADPU Command structure ----------------------------------------------------*/
typedef struct
{
    SC_Header Header;
    SC_Body Body;
} SC_ADPU_Commands;

/* SC response structure -----------------------------------------------------*/
typedef struct
{
    uint8_t Data[LC_MAX];  /* Data returned from the card */
    uint8_t Data_Length;
    uint8_t SW1;          /* Command Processing status */
    uint8_t SW2;          /* Command Processing qualification */
} SC_ADPU_Response;

extern NSString * const GDResponseResultName;                      // 操作结果
extern NSString * const GDResponseMajorVersionName;                // 当前固件主版本号
extern NSString * const GDResponseMinorVersionName;                // 当前固件副版本号
extern NSString * const GDResponseLatestMajorVersionName;          // 最新固件主版本号
extern NSString * const GDResponseLatestMinorVersionName;          // 最新固件副版本号
extern NSString * const GDResponseNeedUpdateName;                  // 是否需要升级
extern NSString * const GDResponseLatestVersionProperty;           // 最新固件特性
extern NSString * const GDDFUInfoPercentageName;                   // 升级进度

typedef NS_ENUM(NSInteger, GDErrorCode) {
    GDSucceed                       = 0,                    // 成功
    GDNetworkError                  = -2101,                // 网络异常
    GDBLEError                      = -3002,                // 蓝牙异常
    GDConnectionError               = -3003,                // 连接异常
    GDTimeoutError                  = -3004,                // 异常超时
    GDNotSupportError               = -3101,                // 设备不支持
    GDInternalError                 = -3102,                // 内部异常
    GDAuthorizationError            = -4001,                // 授权验证失败，请检查AppID、AppKey
};

typedef NS_ENUM(NSInteger, GDFirmwareProperty) {
    GDFirmwarePropertyOptional      = 0,                    // 可选升级
    GDFirmwarePropertyRequired      = 1                     // 必须升级
};

@interface GDUserInfo : NSObject <NSCoding>
@property (nonatomic, assign) int height;                   // 身高 单位：厘米
@property (nonatomic, assign) int weight;                   // 体重 单位：千克
@property (nonatomic, assign) int age;                      // 年龄
@property (nonatomic, assign) int sex;                      // 性别 1:男 2:女
@property (nonatomic, assign) int walkingLength;            // 走路步长 单位：厘米
@property (nonatomic, assign) int runningLength;            // 跑步步长 单位：厘米
@end


typedef NS_OPTIONS(NSUInteger, GDDay) {
    GDDayMon                = 1 <<  0,
    GDDayTues               = 1 <<  1,
    GDDayWed                = 1 <<  2,
    GDDayThur               = 1 <<  3,
    GDDayFri                = 1 <<  4,
    GDDaySat                = 1 <<  5,
    GDDaySun                = 1 <<  6
};

@interface GDBandInfo : NSObject <NSCoding>
@property (nonatomic, assign) int alertBeginHour;           // 活动提醒开始时间 范围：0~23
@property (nonatomic, assign) int alertEndHour;             // 活动提醒结束时间 范围：0~23
@property (nonatomic, assign) int alertInterval;            // 活动提醒间隔 可取值为：10,20,30,40,50,60,70,80,90,100,110,120
// 例：bandInfo.alertDayFlag = GDDayMon | GDDayTues | GDDayWed;表示星期一、二、三开启
@property (nonatomic, assign) int alertDayFlag;             // 活动提醒各天开关
@property (nonatomic, assign) BOOL alertEnable;             // 活动提醒总开关
@property (nonatomic, assign) int alarmHour;                // 智能闹钟时
@property (nonatomic, assign) int alarmMin;                 // 智能闹钟分
@property (nonatomic, assign) int alarmDayFlag;             // 智能闹钟各天开关
@property (nonatomic, assign) BOOL alarmEnable;             // 智能闹钟总开关
@property (nonatomic, assign) int battery;                  // 电池电量 剩余百分比
@end

@interface GDDeviceInfo : NSObject
@property (nonatomic, readonly) int deviceType;             // 设备类型
@property (nonatomic, readonly) int majorVersion;           // 固件主版本号
@property (nonatomic, readonly) int minorVersion;           // 固件副版本号
@property (nonatomic, readonly) NSString *btAddress;        // 设备蓝牙地址
@property (nonatomic, readonly) BOOL hasScreen;             // 是否有屏幕
@property (nonatomic, readonly) BOOL hasVibrator;           // 是否有振动
@property (nonatomic, readonly) BOOL supportAlarm;          // 是否支持闹钟
@property (nonatomic, readonly) BOOL supportAlert;          // 是否支持久坐提醒
@property (nonatomic, readonly) BOOL supportANCS;           // 是否支持ANCS
@property (nonatomic, readonly) BOOL supportWechat;         // 是否支持微信运动
@property (nonatomic, readonly) BOOL supportAPDU;           // 是否支持APDU透传
@end

@interface GDSportData : NSObject
@property (nonatomic, assign) NSTimeInterval time;          // 运动周期起始时间
@property (nonatomic, assign) int step;                     // 该运动周期产生的步数
@property (nonatomic, assign) float calorie;                // 该运动周期产生的卡路里 单位：大卡
@property (nonatomic, assign) int distance;                 // 该运动周期产生的米数 单位：米
@end

@interface GDSleepData : NSObject
@property (nonatomic, assign) NSTimeInterval time;          // 睡眠时间段起始时间
@property (nonatomic, assign) int step;                     // 该睡眠周期内产生的运动量
@end

typedef NS_ENUM(NSInteger, GDSleepState) {
    GDSleepStateGotoSleep = 1,              // 入睡
    GDSleepStateLightSleep,                 // 浅度睡眠
    GDSleepStateDeepSleep,                  // 深度睡眠
    GDSleepStateWakeup,                     // 起夜
    GDSleepStateGetUp                       // 起床
};

@interface GDSleepDetail : NSObject
@property (nonatomic, assign) NSTimeInterval time;
@property (nonatomic, assign) GDSleepState state;
@end

@interface GDSleepDay : NSObject
@property (nonatomic, readonly) NSTimeInterval gotoSleepPoint;                      // 入睡时间 时间戳
@property (nonatomic, readonly) NSTimeInterval getUpPoint;                          // 起床时间 时间戳
@property (nonatomic, readonly) NSTimeInterval lightSleepTime;                      // 浅度睡眠时间 单位：秒
@property (nonatomic, readonly) NSTimeInterval deepSleepTime;                       // 深度睡眠时间 单位：秒
@property (nonatomic, readonly) NSTimeInterval wakeupTime;                          // 起夜时间 单位：秒
@property (nonatomic, readonly) NSArray<GDSleepDetail *> *detailArray;              // 详细睡眠数据
@end

typedef NS_ENUM(NSInteger, GDBandManagerState) {
    GDBandManagerStateDisconnected  = 0,
    GDBandManagerStateScaning,
    GDBandManagerStateConnecting,
    GDBandManagerStateConnected
};

typedef NS_ENUM(NSInteger, GDBandANCSStatus) {
    GDBandANCSStatusOFF             = 0,        // ANCS功能关闭
    GDBandANCSStatusAllOn           = 1,        // 来电和消息提醒都开启
    GDBandANCSStatusCallON          = 2,        // 只开启来电提醒
    GDBandANCSStatusMessageON       = 3         // 只开启消息提醒
};

typedef NS_ENUM(NSInteger, GDBandDFUState) {
    GDBandDFUStateIdle              = 0,        // 空闲状态
    GDBandDFUStatePreparing         = 1,        // 准备中
    GDBandDFUStateWaiting           = 2,        // 等待中
    GDBandDFUStateTransfering       = 3,        // 升级中
};

@protocol GDBandManagerDelegate <NSObject>
@optional
// 搜索到手环回调
- (void)didDiscoverDevice:(CBPeripheral *)peripheral RSSI:(NSNumber *)RSSI;
// 连上手环回调
- (void)didConnectDevice;
// 发送六位随机码回调，需返回六位随机码字符串
- (NSString *)didSendValidateCode;
// 连接失败回调
- (void)didFailToConnectDevice;
// 手环断开连接
- (void)didDisconnectDevice;
// 手机蓝牙状态回调
- (void)centralManagerDidUpdateState:(CBCentralManagerState)state;
@end

@protocol GDBandManagerAPDUDelegate <NSObject>
// 异步发送APDU指令的回调    result:发送是否成功   responseData:返回数据
- (void)didSendApduResult:(BOOL)result responseData:(NSData *)responseData;
@end

@protocol GDBandDFUDelegate <NSObject>
// 固件升级开始
- (void)bandDFUDidStart;
// 回调升级状态
- (void)bandDFUDidUpdateState:(GDBandDFUState)state info:(NSDictionary *)info;
// 固件升级成功
- (void)bandDFUDidComplete;
// 固件升级中断
- (void)bandDFUDidCancelWithError:(NSInteger)errorCode;
@end

@interface GDBandManager : NSObject
@property (nonatomic, readonly) GDBandManagerState state;
@property (nonatomic, readonly) GDBandDFUState dfuState;
@property (nonatomic, readonly) CBCentralManagerState centralManagerState;
@property (nonatomic, readonly) CBPeripheral *currentDevice;
@property (nonatomic, weak) id<GDBandManagerDelegate> delegate;
@property (nonatomic, weak) id<GDBandManagerAPDUDelegate> apduDelegate;
// 初始化方法，请务必填写AppID、AppKey。（showAlert:蓝牙未打开时是否弹出系统提示框）
+ (void)initializeWithAppID:(NSString *)appid appKey:(NSString *)appKey showSystemAlert:(BOOL)showAlert;
+ (GDBandManager *)sharedManager;
// 获取SDK当前版本号
+ (NSString *)sdkVersion;
// 开始搜索手环
- (BOOL)startDiscoverDevice;
// 停止搜索
- (void)stopDiscoverDevice;
// 连接手环。isfirst：是否新绑定手环
- (BOOL)connectDevice:(CBPeripheral *)device isFirst:(BOOL)isfirst;
// 连接外部搜索到的设备（非GDBandManager搜索到的设备）。
- (BOOL)connectOuterDevice:(CBPeripheral *)device isFirst:(BOOL)isfirst;
// 断开连接
- (BOOL)disconnectDevice;
// SE芯片上下电，并返回ATR。enable为YES时上电，NO为下电。
- (BOOL)SEChipOffOn:(BOOL)enable ATR:(uint8_t *)ATR length:(uint8_t *)length timeout:(uint32_t) TimeOut;
// 发送APUD指令并接收返回信息
- (BOOL)APDUSendReceive:(SC_ADPU_Commands *)SC_ADPU response:(SC_ADPU_Response *)SC_Response timeout:(uint32_t) TimeOut;
// 读取BTC info
- (NSData *)getBTCInfoWithTimeout:(uint32_t) TimeOut;
//  透传APDU指令并接收返回信息
- (NSData *)sendAPDUData:(NSData *)data timeout:(uint32_t) TimeOut;
- (NSData *)sendData:(NSData *)data timeout:(uint32_t) TimeOut;
// 异步发送APDU指令，通过apduDelegate回调发送结果（返回值为YES时表示调用成功且必有回调，请等待回调后再进行下一次调用）。
- (BOOL)asyncSendAPDUData:(NSData *)data;

/*
 运动数据相关接口
 */

// 获取设备类型以及固件版本号
- (BOOL)getDeviceTypeAndVersion:(void(^)(BOOL success, int type, int versionMajor, int versionMinor))completion;
// 获取设备内存储的用户信息
- (BOOL)getUserInfo:(void(^)(BOOL success, GDUserInfo *userInfo))completion;
// 获取设备内存储的手环信息
- (BOOL)getBandInfo:(void(^)(BOOL success, GDBandInfo *bandInfo))completion;
// 更新用户信息
- (BOOL)updateUserInfo:(GDUserInfo *)userInfo completion:(void(^)(BOOL success))completion;
// 更新手环信息
- (BOOL)updateBandInfo:(GDBandInfo *)bandInfo completion:(void(^)(BOOL success))completion;
// 更新设备时间
- (BOOL)updateDeviceTime:(void(^)(BOOL success))completion;
// 获取设备内存储的运动数据和睡眠数据
- (BOOL)getSportAndSleepData:(void(^)(BOOL success, NSArray *sportDataAry, NSArray *sleepDataAry))completion;
// 获取设备内存储的运动数据和睡眠数据(睡眠算法结果)
- (BOOL)getSportAndSleepResult:(void(^)(BOOL success, NSArray *sportDataAry, GDSleepDay *sleepDay))completion;
// 清除设备内存储的运动数据和睡眠数据
- (BOOL)clearSportAndSleepData:(void(^)(BOOL success))completion;
// 获取手环当前的实时步数和卡路里
- (BOOL)getRealTimeStepAndCalorie:(void(^)(BOOL success, int step, float calorie))completion;
// 获取手环当前的ANCS状态
- (BOOL)getBandANCSStatus:(void(^)(BOOL success, GDBandANCSStatus status))completion;
// 设置手环当前的ANCS状态
/*
    注意：如果手环连接手机的时候状态为GDBandANCSStatusOFF，
    此时设置为其他开启状态后，都需要手环和手机重新连接才能正常收到ANCS消息。
 */
- (BOOL)updateBandANCSStatus:(GDBandANCSStatus)status completion:(void(^)(BOOL success))completion;

// 获取手环当前的实时步数、卡路里和距离（新版接口）
- (BOOL)getRealTimeStepCalorieDistance:(void(^)(BOOL success, int step, float calorie, float distance))completion;
// 清除手环显示的步数卡路里
- (BOOL)clearRealTimeDataWithCompletion:(void(^)(BOOL success))completion;

// 注册微信运动
- (BOOL)registerWechatSport:(void(^)(BOOL success))completion;
// 查询微信运动注册状态
- (BOOL)queryWechatSportStatus:(void(^)(BOOL success, BOOL isOpen))completion;

// 检查固件是否有更新
- (BOOL)checkBandFirmwareVersion:(void(^)(NSDictionary *response))completion;
// 升级最新的固件（必须先调用检查接口）
- (BOOL)startDFUWithDelegate:(id<GDBandDFUDelegate>)delegate;
// 获取当前设备信息
- (GDDeviceInfo *)currentDeviceInfo;
@end


