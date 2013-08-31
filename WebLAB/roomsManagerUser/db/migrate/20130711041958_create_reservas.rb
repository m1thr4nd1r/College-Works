class CreateReservas < ActiveRecord::Migration
  def change
    create_table :reservas do |t|
      t.string :data_inicio
      t.string :responsavel

      t.timestamps
    end
  end
end
