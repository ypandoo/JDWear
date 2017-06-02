import { NgModule } from '@angular/core';
import { IonicPageModule } from 'ionic-angular';
import { LanguageSetActivityPage } from './language-set-activity';

@NgModule({
  declarations: [
    LanguageSetActivityPage,
  ],
  imports: [
    IonicPageModule.forChild(LanguageSetActivityPage),
  ],
  exports: [
    LanguageSetActivityPage
  ]
})
export class LanguageSetActivityPageModule {}
