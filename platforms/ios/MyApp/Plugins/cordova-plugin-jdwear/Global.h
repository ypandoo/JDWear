//
//  Global.h
//  ShenZhen
//
//  Created by 捷徳 on 16/5/26.
//  Copyright © 2016年 捷徳. All rights reserved.
//

#import "lib/GDBandSDK.h"
extern NSString * const kGDBandMangerId;               //手环sdk的id
extern NSString * const kGDBandMangerKey;              //手环sdk的key
extern NSString * const kGDLastDevice;                 //存储绑定手环的name，方便下次进来直接扫描自动绑定

extern NSString * const NETSETTING;                    //下载环境设置


@interface Global : NSObject<GDBandManagerDelegate>
@property(nonatomic,strong)CBPeripheral *selectedDevice;  //选中的手环
@property(nonatomic,strong)GDBandManager *bandManager;
@property(nonatomic,assign)BOOL channelConnected;
@property(nonatomic,copy)NSString * channelID;
@property(nonatomic,strong)NSString *selectedDeviceName;       //选中手环的name
@property(nonatomic,strong)NSMutableArray *deviceMutarray;     //扫描到的手环
@property(nonatomic,strong)NSMutableDictionary *deviceMutdic;  //扫描到的手环及对应的信号强度
@property(nonatomic,strong)NSString *tipstr;//连接手环显示的数字
@property(nonatomic,assign)BOOL isSeUp;
@property(nonatomic,assign)BOOL userType; // 很重要，用户类型，YES 为手环用户  NO 为手机用户
@property(nonatomic,strong)NSString * currentLanguage;   //当前的系统语言，做为网络接口的参数
@property(nonatomic,assign)NSInteger bluetoothState;   //当前的系统语言，做为网络接口的参数
@property(nonatomic,strong)NSMutableArray *currentSportArray;
+(instancetype)shareGlobal;

//扫描周围设备
-(void)startDiscoverDevices;

@end

