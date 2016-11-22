class controllerData {
public:
  //! Default constructor
  controllerData();

  //! Copy constructor
  controllerData(const controllerData &other);

  //! Move constructor
  controllerData(controllerData &&other) noexcept;

  //! Destructor
  virtual ~controllerData() noexcept;

  //! Copy assignment operator
  controllerData &operator=(const controllerData &other);

  //! Move assignment operator
  controllerData &operator=(controllerData &&other) noexcept;

  double throttle;
  double ccmSP;
  double ccmKP;
  double ccmKI;
  double scmSP;
  double scmKP;
  double scmKI;

protected:
private:
};
