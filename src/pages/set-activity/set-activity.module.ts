import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { SetActivityPage } from './set-activity';

@NgModule({
  declarations: [
    SetActivityPage,
  ],
  imports: [
    IonicPageModule.forChild(SetActivityPage),
  ],
  exports: [
    SetActivityPage
  ]
})
export class SetActivityPageModule {}
