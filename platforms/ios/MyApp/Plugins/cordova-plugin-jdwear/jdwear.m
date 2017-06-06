/********* jdwear.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import "Global.h"

@interface jdwear : CDVPlugin {
    id search_call_back_id;
}

- (void)coolMethod:(CDVInvokedUrlCommand*)command;
@end

@implementation jdwear

- (void)pluginInitialize{
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(didDiscoverDevice) name:@"PLUGIN_NOTIFICATION_DID_DICOVER_DEVICE" object:nil];
}

- (void)coolMethod:(CDVInvokedUrlCommand*)command
{
    NSLog(@"coolMethod");

    CDVPluginResult* pluginResult = nil;
    NSString* echo = @"start searching device...";
    
    [[Global shareGlobal] startDiscoverDevices];

    if (echo != nil && [echo length] > 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    search_call_back_id = command.callbackId;
    [pluginResult setKeepCallbackAsBool:TRUE];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    
}

- (void)didDiscoverDevice
{
    NSString* echo = @"success find device";
    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:search_call_back_id];
    NSLog(@"didDiscoverDevice");
}
@end
