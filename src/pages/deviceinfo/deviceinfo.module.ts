import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { DeviceinfoPage } from './deviceinfo';

@NgModule({
  declarations: [
    DeviceinfoPage,
  ],
  imports: [
    IonicPageModule.forChild(DeviceinfoPage),
  ],
  exports: [
    DeviceinfoPage
  ]
})
export class DeviceinfoPageModule {}
