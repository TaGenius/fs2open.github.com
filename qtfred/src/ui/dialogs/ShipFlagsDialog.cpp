#include "ShipFlagsDialog.h"

#include "ui_ShipFlagsDialog.h"

#include <ui/util/SignalBlockers.h>

#include <QCloseEvent>

namespace fso {
namespace fred {
namespace dialogs {

ShipFlagsDialog::ShipFlagsDialog(QWidget* parent, EditorViewport* viewport)
	: QDialog(parent), ui(new Ui::ShipFlagsDialog()), _model(new ShipFlagsDialogModel(this, viewport)),
	  _viewport(viewport)
{
	ui->setupUi(this);

	connect(this, &QDialog::accepted, _model.get(), &ShipFlagsDialogModel::apply);
	connect(this, &QDialog::rejected, _model.get(), &ShipFlagsDialogModel::reject);

	connect(_model.get(), &AbstractDialogModel::modelChanged, this, &ShipFlagsDialog::updateUI);
	
	//Column One
	connect(ui->destroyBeforeMissionCheckbox, &QCheckBox::toggled, this, &ShipFlagsDialog::destroyBeforeMissionChanged);

	updateUI();

	// Resize the dialog to the minimum size
	resize(QDialog::sizeHint());
}

ShipFlagsDialog::~ShipFlagsDialog() {}

void ShipFlagsDialog::closeEvent(QCloseEvent* event)
{
	if (_model->query_modified()) {
		auto button = _viewport->dialogProvider->showButtonDialog(DialogType::Question,
			"Changes detected",
			"Do you want to keep your changes?",
			{DialogButton::Yes, DialogButton::No, DialogButton::Cancel});

		if (button == DialogButton::Cancel) {
			event->ignore();
			return;
		}

		if (button == DialogButton::Yes) {
			accept();
			return;
		}
	}

	QDialog::closeEvent(event);
}

void ShipFlagsDialog::updateUI() {
	util::SignalBlockers blockers(this);

	//Column One
	auto value = _model->getDestroyed();
	ui->destroyBeforeMissionCheckbox->setChecked(value);
}

void ShipFlagsDialog::destroyBeforeMissionChanged(bool value)
{
	_model->setDestroyed(value);
}

} // namespace dialogs
} // namespace fred
} // namespace fso