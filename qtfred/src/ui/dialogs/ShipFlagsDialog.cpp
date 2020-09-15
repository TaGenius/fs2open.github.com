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

	// Column One
	connect(ui->destroyBeforeMissionCheckbox,
		&QCheckBox::stateChanged,
		this,
		&ShipFlagsDialog::destroyBeforeMissionChanged);
	connect(ui->destroySecondsSpinBox,
		static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this,
		&ShipFlagsDialog::destroyBeforeMissionSecondsChanged);
	connect(ui->scanableCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::scanableChanged);
	connect(ui->cargoKnownCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::cargoChanged);
	connect(ui->toggleSubsytemScanningCheckbox,
		&QCheckBox::stateChanged,
		this,
		&ShipFlagsDialog::subsytemScanningChanged);
	connect(ui->reinforcementUnitCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::reinforcementChanged);
	connect(ui->protectShipCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::protectShipChanged);
	connect(ui->beamProtectCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::beamProtectChanged);
	connect(ui->flakProtectCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::flakProtectChanged);
	connect(ui->laserProtectCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::laserProtectChanged);
	connect(ui->missileProtectCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::missileProtectChanged);
	connect(ui->ignoreForGoalsCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::ignoreForGoalsChanged);
	connect(ui->escortShipCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::escortChanged);
	connect(ui->escortPrioritySpinBox,
		static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this,
		&ShipFlagsDialog::escortValueChanged);
	connect(ui->noArrivalMusicCheckBox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::noArrivalMusicChanged);
	connect(ui->invulnerableCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::invulnerableChanged);
	connect(ui->guardianedCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::guardianedChanged);
	connect(ui->primitiveCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::primitiveChanged);
	connect(ui->noSubspaceDriveCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::noSubspaceChanged);
	connect(ui->hiddenFromSensorsCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::hiddenChanged);
	connect(ui->stealthCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::stealthChanged);
	connect(ui->friendlyStealthCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::friendlyStealthChanged);
	connect(ui->kamikazeCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::kamikazeChanged);
	connect(ui->kamikazeDamageSpinBox,
		static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this,
		&ShipFlagsDialog::kamikazeDamageChanged);
	connect(ui->noMoveCheckbox, &QCheckBox::stateChanged, this, &ShipFlagsDialog::immobileChanged);

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

void ShipFlagsDialog::updateUI()
{
	util::SignalBlockers blockers(this);

	// Column One
	// Destroy before mission
	auto value = _model->getDestroyed();
	ui->destroyBeforeMissionCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getDestroyedSeconds();
	ui->destroySecondsSpinBox->setValue(value);
	// Scanable
	value = _model->getScanable();
	ui->scanableCheckbox->setCheckState(Qt::CheckState(value));
	// Cargo known
	value = _model->getCargoKnown();
	ui->cargoKnownCheckbox->setCheckState(Qt::CheckState(value));
	// Toggle Subsytem Sacnning
	value = _model->getSubsystemScanning();
	ui->toggleSubsytemScanningCheckbox->setCheckState(Qt::CheckState(value));
	// Reinforcement
	value = _model->getReinforcment();
	ui->reinforcementUnitCheckbox->setCheckState(Qt::CheckState(value));
	// Protect Flags
	value = _model->getProtectShip();
	ui->protectShipCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getBeamProtect();
	ui->beamProtectCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getFlakProtect();
	ui->flakProtectCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getLaserProtect();
	ui->laserProtectCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getMissileProtect();
	ui->missileProtectCheckbox->setCheckState(Qt::CheckState(value));
	// Ignore For goals
	value = _model->getIgnoreForGoals();
	ui->ignoreForGoalsCheckbox->setCheckState(Qt::CheckState(value));
	// Escort
	value = _model->getEscort();
	ui->escortShipCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getEscortValue();
	ui->escortPrioritySpinBox->setValue(value);
	// No Arrival Music
	value = _model->getNoArrivalMusic();
	ui->noArrivalMusicCheckBox->setCheckState(Qt::CheckState(value));
	// Invulnerable
	value = _model->getInvulnerable();
	ui->invulnerableCheckbox->setCheckState(Qt::CheckState(value));
	// Guardiened
	value = _model->getGuardianed();
	ui->guardianedCheckbox->setCheckState(Qt::CheckState(value));
	// Pirmitive Sensors
	value = _model->getPrimitiveSensors();
	ui->primitiveCheckbox->setCheckState(Qt::CheckState(value));
	// No Subspace Drive
	value = _model->getNoSubspaceDrive();
	ui->noSubspaceDriveCheckbox->setCheckState(Qt::CheckState(value));
	// Hidden From Sensors
	value = _model->getHidden();
	ui->hiddenFromSensorsCheckbox->setCheckState(Qt::CheckState(value));
	// Stealth
	value = _model->getStealth();
	ui->stealthCheckbox->setCheckState(Qt::CheckState(value));
	// Freindly Stealth
	value = _model->getFriendlyStealth();
	ui->friendlyStealthCheckbox->setCheckState(Qt::CheckState(value));
	// Kamikaze
	value = _model->getKamikaze();
	ui->kamikazeCheckbox->setCheckState(Qt::CheckState(value));
	value = _model->getKamikazeDamage();
	ui->kamikazeDamageSpinBox->setValue(value);
	//Does Not move
	value = _model->getImmobile();
	ui->noMoveCheckbox->setCheckState(Qt::CheckState(value));
}

void ShipFlagsDialog::destroyBeforeMissionChanged(int value)
{
	_model->setDestroyed(value);
}

void ShipFlagsDialog::destroyBeforeMissionSecondsChanged(int value)
{
	_model->setDestroyedSeconds(value);
}

void ShipFlagsDialog::scanableChanged(int value)
{
	_model->setScanable(value);
}

void ShipFlagsDialog::cargoChanged(int value)
{
	_model->setCargoKnown(value);
}

void ShipFlagsDialog::subsytemScanningChanged(int value)
{
	_model->setSubsystemScanning(value);
}

void ShipFlagsDialog::reinforcementChanged(int value)
{
	_model->setReinforcment(value);
}

void ShipFlagsDialog::protectShipChanged(int value)
{
	_model->setProtectShip(value);
}

void ShipFlagsDialog::beamProtectChanged(int value)
{
	_model->setBeamProtect(value);
}

void ShipFlagsDialog::flakProtectChanged(int value)
{
	_model->setFlakProtect(value);
}

void ShipFlagsDialog::laserProtectChanged(int value)
{
	_model->setLaserProtect(value);
}

void ShipFlagsDialog::missileProtectChanged(int value)
{
	_model->setMissileProtect(value);
}

void ShipFlagsDialog::ignoreForGoalsChanged(int value)
{
	_model->setIgnoreForGoals(value);
}

void ShipFlagsDialog::escortChanged(int value)
{
	_model->setEscort(value);
}

void ShipFlagsDialog::escortValueChanged(int value)
{
	_model->setEscortValue(value);
}

void ShipFlagsDialog::noArrivalMusicChanged(int value)
{
	_model->setNoArrivalMusic(value);
}

void ShipFlagsDialog::invulnerableChanged(int value)
{
	_model->setInvulnerable(value);
}

void ShipFlagsDialog::guardianedChanged(int value)
{
	_model->setGuardianed(value);
}

void ShipFlagsDialog::primitiveChanged(int value)
{
	_model->setPrimitiveSensors(value);
}

void ShipFlagsDialog::noSubspaceChanged(int value)
{
	_model->setNoSubspaceDrive(value);
}

void ShipFlagsDialog::hiddenChanged(int value)
{
	_model->setHidden(value);
}

void ShipFlagsDialog::stealthChanged(int value)
{
	_model->setStealth(value);
}

void ShipFlagsDialog::friendlyStealthChanged(int value)
{
	_model->setFriendlyStealth(value);
}

void ShipFlagsDialog::kamikazeChanged(int value)
{
	_model->setKamikaze(value);
}

void ShipFlagsDialog::kamikazeDamageChanged(int value)
{
	_model->setKamikazeDamage(value);
}

void ShipFlagsDialog::immobileChanged(int value)
{
	_model->setImmobile(value);
}

} // namespace dialogs
} // namespace fred
} // namespace fso