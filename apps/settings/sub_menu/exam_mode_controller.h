#ifndef SETTINGS_EXAM_MODE_CONTROLLER_H
#define SETTINGS_EXAM_MODE_CONTROLLER_H

#include "generic_sub_controller.h"
#include "preferences_controller.h"

namespace Settings {

class ExamModeController : public GenericSubController {
public:
  ExamModeController(Responder * parentResponder);
  bool handleEvent(Ion::Events::Event event) override;
  int numberOfRows() const override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
  int typeAtLocation(int i, int j) override;
private:
  MessageTableCell m_examModeCell;
  MessageTableCellWithChevronAndMessage m_ledCell;
  PreferencesController m_preferencesController;
  MessageTableCellWithSwitch m_symbolicCell;
  int initialSelectedRow() const override;
  static constexpr int k_maxNumberOfCells = 2;
  MessageTableCell m_cell[k_maxNumberOfCells];
};

}

#endif
