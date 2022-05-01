#include "UIManager.h"

void UIManager::uiMouseInputManagement(int button, int state, int wheel, int direction, int x, int y) {
   btnManager->inputManagement(x, y, &state);
   imgEditor->inputManagement(x, y, state);
   sldManager->inputManagement(x, y, &state);

   mouseX = x; mouseY = y; mouseState = state;
}

void UIManager::uiKeyboardInputManagement(int key, bool keyUp) {
   if (keyUp && key == 49)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\arizona.bmp");

   if (keyUp && key == 50)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\lena.bmp");

   if (keyUp && key == 51)
      imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\baboon.bmp");
}

void UIManager::drawBackground() {
   CV::color(1,1,1);
   CV::rectFill(collisionX - bgLineThickness, 0, collisionX, screenHeight);
   CV::rectFill(collisionX, collisionY + bgLineThickness, screenWidth, collisionY);
   CV::text(collisionX + btnSpacingX, collisionY + btnSpacingY + bgLineThickness*2, imgEditor->getImageName().c_str());
}

void UIManager::uiRender() {
   btnManager->renderButtons(mouseX, mouseY, mouseState);
   imgEditor->renderImages();
   sldManager->renderSliders();

   if (imgEditor->listenToImageChange()) {
      std::vector<Image*> images = imgEditor->getImages();
      std::vector<Image::Filter> filters = images[imgEditor->getCurrentImageIndex()]->getActiveFilters();
      btnManager->setButtonState(filters);
      int brightness = images[imgEditor->getCurrentImageIndex()]->getBrightness();
      int contrast   = images[imgEditor->getCurrentImageIndex()]->getContrast();
      sldManager->setSliderState(brightness, contrast);
   }

   drawBackground();
}

void UIManager::uiCreate() {
   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - (btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnSwitch, screenHeight - btnSpacingY), "A",
                         [this]() { imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\arizona.bmp"); });

   btnManager->addButton(new Vector2(2*btnSpacingX + btnSwitch, screenHeight - (btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnSwitch, screenHeight - btnSpacingY), "B",
                         [this]() { imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\lena.bmp"); });

   btnManager->addButton(new Vector2(3*btnSpacingX + 2*btnSwitch, screenHeight - (btnHeight + btnSpacingY)),
                         new Vector2(3*btnSpacingX + 3*btnSwitch, screenHeight - btnSpacingY), "C",
                         [this]() { imgEditor->addImage(this->screenWidth*0.7, 1, ".\\Trab 1 lamilitz\\resources\\baboon.bmp"); });

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 2*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnBigWidth, screenHeight - (btnHeight + 2*btnSpacingY)), "Delete Image",
                         [this]() { imgEditor->deleteImage(); btnManager->resetButtonState(); sldManager->resetSliders(); });

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 3*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY)), "R",
                         [this]() { imgEditor->setColorFilter(Image::Filter::red); }, Button::Color::red, true);

   btnManager->addButton(new Vector2(2*btnSpacingX + btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY)), "G",
                         [this]() { imgEditor->setColorFilter(Image::Filter::green); }, (Button::Color) Button::Color::green, true);

   btnManager->addButton(new Vector2(3*btnSpacingX + 2*btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY)),
                         new Vector2(3*btnSpacingX + 3*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY)), "B",
                         [this]() { imgEditor->setColorFilter(Image::Filter::blue); }, Button::Color::blue, true);

   btnManager->addButton(new Vector2(4*btnSpacingX + 3*btnSmallWidth, screenHeight - 3*(btnHeight + btnSpacingY)),
                         new Vector2(4*btnSpacingX + 4*btnSmallWidth, screenHeight - (2*btnHeight + 3*btnSpacingY)), "L",
                         [this]() { imgEditor->setColorFilter(Image::Filter::luminance); }, Button::Color::light, true);

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 4*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnMedWidth, screenHeight - (3*btnHeight + 4*btnSpacingY)), "Invert",
                         [this]() { imgEditor->setColorFilter(Image::Filter::inverted); });

   btnManager->addButton(new Vector2(2*btnSpacingX + btnMedWidth, screenHeight - 4*(btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnMedWidth, screenHeight - (3*btnHeight + 4*btnSpacingY)), "BGR<->RGB",
                         [this]() { imgEditor->setColorFilter(Image::Filter::bgr); });

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 5*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnMedWidth, screenHeight - (4*btnHeight + 5*btnSpacingY)), "Flip Hor.",
                         [this]() { imgEditor->flipHorizontal(); });

   btnManager->addButton(new Vector2(2*btnSpacingX + btnMedWidth, screenHeight - 5*(btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnMedWidth, screenHeight - (4*btnHeight + 5*btnSpacingY)), "Flip Ver.",
                         [this]() { imgEditor->flipVertical(); });

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 6*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnMedWidth, screenHeight - (5*btnHeight + 6*btnSpacingY)), "Rotate Left",
                         [this]() { imgEditor->rotateImg(0); });

   btnManager->addButton(new Vector2(2*btnSpacingX + btnMedWidth, screenHeight - 6*(btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnMedWidth, screenHeight - (5*btnHeight + 6*btnSpacingY)), "Rotate Right",
                         [this]() { imgEditor->rotateImg(1); });

   btnManager->addButton(new Vector2(btnSpacingX, screenHeight - 7*(btnHeight + btnSpacingY)),
                         new Vector2(btnSpacingX + btnMedWidth, screenHeight - (6*btnHeight + 7*btnSpacingY)), "Scale 200%",
                         [this]() { imgEditor->resizeImage(2); });

   btnManager->addButton(new Vector2(2*btnSpacingX + btnMedWidth, screenHeight - 7*(btnHeight + btnSpacingY)),
                         new Vector2(2*btnSpacingX + 2*btnMedWidth, screenHeight - (6*btnHeight + 7*btnSpacingY)), "Scale 50%",
                         [this]() { imgEditor->resizeImage(0.5); });

   sldManager->addSlider(-255, 255, btnSpacingX, screenHeight - 8*(btnHeight + btnSpacingY), btnBigWidth, "Brightness",
                         [this]() { imgEditor->setBrightness(sldManager->getValue()); });

   sldManager->addSlider(-255, 255, btnSpacingX, screenHeight - 9*(btnHeight + btnSpacingY), btnBigWidth, "Contrast",
                         [this]() { imgEditor->setContrast(sldManager->getValue()); });
}

UIManager::UIManager(int screenWidth, int screenHeight) {
   this->screenWidth  = screenWidth;
   this->screenHeight = screenHeight;

   bgLineThickness      = 5;
   btnSpacingX    = 0.01*screenWidth;
   btnSpacingY    = 0.02*screenHeight;
   btnHeight      = screenHeight*0.0417;
   btnBigWidth    = screenWidth*0.2845;
   btnMedWidth    = (btnBigWidth - btnSpacingX)/2;
   btnSwitch      = (btnBigWidth - 2*btnSpacingX)/3;
   btnSmallWidth  = (btnBigWidth - 3*btnSpacingX)/4;
   collisionX     = btnBigWidth + bgLineThickness + btnSpacingX*3;
   collisionY     = screenHeight - btnHeight - btnSpacingY - bgLineThickness;

   btnManager = new ButtonManager();
   sldManager = new SliderManager();
   imgEditor  = new ImageEditor(new ColorHistogram(btnSpacingX, btnSpacingY, screenWidth*0.2834, screenHeight*0.3666));

   uiCreate();
}
