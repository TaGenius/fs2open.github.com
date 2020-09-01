#ifndef SHIPFLAGDIALOG_H
#define SHIPFLAGDIALOG_H

#include <mission/dialogs/ShipFlagsDialogModel.h>
#include <ui/FredView.h>

#include <QtWidgets/QDialog>

namespace fso {
namespace fred {
namespace dialogs {

namespace Ui {
class ShipFlagsDialog;
}

class ShipFlagsDialog : public QDialog {
	Q_OBJECT

  public:
	explicit ShipFlagsDialog(QWidget* parent, EditorViewport* viewport);
	~ShipFlagsDialog() override;

  protected:
	void closeEvent(QCloseEvent*) override;

  private:
	std::unique_ptr<Ui::ShipFlagsDialog> ui;
	std::unique_ptr<ShipFlagsDialogModel> _model;
	EditorViewport* _viewport;

	void updateUI();

	void destroyBeforeMissionChanged(bool);
};
} // namespace dialogs
} // namespace fred
} // namespace fso

#endif // !SHIPFLAGDIALOG_H