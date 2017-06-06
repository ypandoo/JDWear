//
//  Global.m
//  ShenZhen
//
//  Created by 捷徳 on 16/5/26.
//  Copyright © 2016年 捷徳. All rights reserved.
//

#import "Global.h"

@interface Global()
@property (nonatomic,copy)NSString *atrStr;
@end
NSString * const kGDBandMangerId = @"20029";
NSString * const kGDBandMangerKey = @"bc2789825bbba0b6bdeac8b3f53ccc79";
NSString * const kGDLastDevice = @"lastSelectDevice";


@implementation Global
{
    BOOL sportFlag ;
    BOOL sleepFlag ;
    BOOL UNbindFlag; //解绑成功的标志，同样回调函数里做判断用
    BOOL RbindFlag;//设置来电短信提醒需要重新连接手环，此标志作用不做回调处理
}
+(instancetype)shareGlobal
{
    static Global *shareGlobalInstance = nil;
    static dispatch_once_t p;
    dispatch_once(&p, ^{
        shareGlobalInstance = [[self alloc]init];
        [shareGlobalInstance initGDbandManger];
    });
    return shareGlobalInstance;
}
-(void)initGDbandManger
{
    [GDBandManager initializeWithAppID:kGDBandMangerId appKey:kGDBandMangerKey showSystemAlert:YES];
    self.bandManager = [GDBandManager sharedManager];
    [self.bandManager setDelegate:self];
    self.bandManager.apduDelegate = self;
    self.deviceMutarray = [[NSMutableArray alloc]init];
    self.deviceMutdic = [[NSMutableDictionary alloc]init];
    UNbindFlag = NO;
    self.channelConnected = NO;
    self.channelID = nil;
    self.atrStr = nil;
}
#pragma mark - GDBandManagerDelegate
#pragma mark - 手环的回调
// 搜索到手环回调
- (void)didDiscoverDevice:(CBPeripheral *)peripheral RSSI:(NSNumber *)RSSI
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!self.selectedDeviceName) {
            self.selectedDeviceName = [[NSUserDefaults standardUserDefaults]objectForKey:kGDLastDevice];
        }
        NSLog(@"self.selectedDeviceName=================%@",self.selectedDeviceName);
        NSLog(@"peripheral.name==========%@",peripheral.name);
        if (self.selectedDeviceName) {
            if ([peripheral.name isEqualToString:self.selectedDeviceName]) {
                self.selectedDevice = peripheral;
                [self.bandManager stopDiscoverDevice];
                //[self connectDevice:self.selectedDevice isFirst:NO];
            }
        }
        if (![self.deviceMutarray containsObject:peripheral]) {
            [self.deviceMutarray addObject:peripheral];
        }
        [self.deviceMutdic setObject:RSSI forKey:peripheral];
        if (self.selectedDevice)
        {
            [self.deviceMutarray removeObject:self.selectedDevice];
            [self.deviceMutdic removeObjectForKey:self.selectedDevice];
        }
        [[NSNotificationCenter defaultCenter]postNotificationName:@"PLUGIN_NOTIFICATION_DID_DICOVER_DEVICE" object:self];
    });
}

#pragma mark---封装的方法
//扫描周围设备
-(void)startDiscoverDevices
{
    [[Global shareGlobal].deviceMutarray removeAllObjects];
    [[Global shareGlobal].deviceMutdic removeAllObjects];
    [self.bandManager startDiscoverDevice];
}
@end
