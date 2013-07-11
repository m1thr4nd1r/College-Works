# encoding: UTF-8
# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20130711041958) do

  create_table "equipamento", :force => true do |t|
    t.string  "descricao", :limit => 45,                    :null => false
    t.integer "sala_id"
    t.boolean "is_fixo",                 :default => false, :null => false
  end

  add_index "equipamento", ["sala_id"], :name => "fk_equipamento_sala1"

  create_table "grupo", :force => true do |t|
    t.string "nome",                  :limit => 60, :null => false
    t.string "professor_responsavel", :limit => 60
  end

  create_table "grupo_has_sala", :id => false, :force => true do |t|
    t.integer "grupo_id", :null => false
    t.integer "sala_id",  :null => false
  end

  add_index "grupo_has_sala", ["grupo_id"], :name => "fk_grupo_has_sala_grupo1_idx"
  add_index "grupo_has_sala", ["sala_id"], :name => "fk_grupo_has_sala_sala1_idx"

  create_table "pessoa", :force => true do |t|
    t.integer "numMatricula",                                  :null => false
    t.string  "nome",         :limit => 60,                    :null => false
    t.boolean "is_professor",               :default => false, :null => false
  end

  add_index "pessoa", ["numMatricula"], :name => "numMatricula_UNIQUE", :unique => true

  create_table "pessoa_has_grupo", :id => false, :force => true do |t|
    t.integer "grupo_id",  :null => false
    t.integer "pessoa_id", :null => false
  end

  add_index "pessoa_has_grupo", ["grupo_id"], :name => "fk_aluno_grupo_1"
  add_index "pessoa_has_grupo", ["pessoa_id"], :name => "fk_aluno_grupo_2"

  create_table "reserva_sala", :force => true do |t|
    t.integer "sala_id",                        :null => false
    t.date    "data_inicio",                    :null => false
    t.date    "data_fim"
    t.time    "horario_inicio",                 :null => false
    t.time    "horario_termino"
    t.string  "responsavel",     :limit => 45,  :null => false
    t.string  "reserva_para",    :limit => 256
    t.boolean "evento_privado",                 :null => false
    t.string  "email",           :limit => 45
    t.string  "telefone",        :limit => 45
    t.string  "obs",             :limit => 256
  end

  add_index "reserva_sala", ["sala_id"], :name => "fk_solicitar_reserva_1_idx"

  create_table "reservas", :force => true do |t|
    t.string   "data_inicio"
    t.string   "responsavel"
    t.datetime "created_at",  :null => false
    t.datetime "updated_at",  :null => false
  end

  create_table "sala", :id => false, :force => true do |t|
    t.integer "id",                                                :null => false
    t.string  "nome",            :limit => 100,                    :null => false
    t.boolean "quadro",                         :default => false, :null => false
    t.boolean "retroprojetor",                  :default => false, :null => false
    t.boolean "multimidia",                     :default => false, :null => false
    t.string  "tipo",            :limit => 60,                     :null => false
    t.boolean "ar_condicionado",                :default => false, :null => false
    t.integer "computadores",                   :default => 0,     :null => false
    t.integer "capacidade",                                        :null => false
    t.integer "setor_id",                                          :null => false
  end

  add_index "sala", ["setor_id"], :name => "fk_sala_setores1"

  create_table "setor", :force => true do |t|
    t.string "nome",  :limit => 100, :null => false
    t.string "email", :limit => 100, :null => false
  end

  create_table "solicitacao_equipamento", :id => false, :force => true do |t|
    t.integer "equipamento_id", :null => false
    t.integer "pessoa_id",      :null => false
  end

  add_index "solicitacao_equipamento", ["equipamento_id"], :name => "fk_solicitacao_equipamento_2"
  add_index "solicitacao_equipamento", ["pessoa_id"], :name => "fk_solicitacao_equipamento_1"

  create_table "usuario", :force => true do |t|
    t.string  "tipo",         :limit => 45,  :null => false
    t.string  "email",        :limit => 60,  :null => false
    t.string  "nome",         :limit => 100, :null => false
    t.string  "senha",        :limit => 64,  :null => false
    t.integer "num_cadastro",                :null => false
  end

  add_index "usuario", ["email"], :name => "email_UNIQUE", :unique => true
  add_index "usuario", ["num_cadastro"], :name => "num_cadastro_UNIQUE", :unique => true

end
